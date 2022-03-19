#include "vlc.h"

#include <assert.h>
#include <QtWidgets/QWidget>

# ifdef __cplusplus
extern "C" {
# endif
#include <vlc/vlc.h>
# ifdef __cplusplus
}
# endif

unsigned int VLC::s_ref = 0;
libvlc_instance_t *VLC::s_pVlcInstance = NULL;

VLC::VLC(QWidget* pWidget)
	: IMediaPlayer(pWidget)
	, m_pVlcPlayer(NULL)
{
	/* Initialize libVLC */
	if (0 == s_ref++)
	{
		s_pVlcInstance = libvlc_new(0, NULL);
		if (NULL == s_pVlcInstance)
		{
			assert(false);
		}
	}
}


VLC::~VLC()
{
	if (0 == --s_ref)
	{
		libvlc_release(s_pVlcInstance);
	}
}

bool VLC::Open(const char *url)
{
	/* Stop if something is playing */
	//if (m_pVlcPlayer && libvlc_media_player_is_playing(m_pVlcPlayer))
	//{
	//    Stop();
	//}
	Stop();

	auto funcOpen = libvlc_media_new_path;
	if (QString(url).startsWith("rtsp://") ||
		QString(url).startsWith("rtmp://") ||
		QString(url).startsWith("rtp://") ||
		QString(url).startsWith("tcp://") ||
		QString(url).startsWith("udp://") ||
		QString(url).startsWith("ftp://") ||
		QString(url).startsWith("http://") ||
		QString(url).startsWith("https://"))
	{
		funcOpen = libvlc_media_new_location;
	}

	/* Create a new Media */
	libvlc_media_t *vlcMedia = funcOpen(s_pVlcInstance, url);
	/* Fail to open url*/
	if (!vlcMedia)
	{
		return false;
	}

	if (QString(url).endsWith(".hevc"))
		libvlc_media_add_option(vlcMedia, ":demux=hevc");
	else if (QString(url).endsWith("rtsp"))
		libvlc_media_add_option(vlcMedia, ":rtsp-tcp");

	libvlc_media_add_option(vlcMedia, ":network-caching=100");
	libvlc_media_add_option(vlcMedia, ":sout-display-delay=0");
	libvlc_media_add_option(vlcMedia, ":sout-ts-dts-delay=0");
	libvlc_media_add_option(vlcMedia, ":sout-ps-dts-delay=0");
	libvlc_media_add_option(vlcMedia, ":sout-mux-caching=1");
	libvlc_media_add_option(vlcMedia, ":live-caching=1");

	/* Create a new libvlc player */
	m_pVlcPlayer = libvlc_media_player_new_from_media(vlcMedia);

	/* Release the media */
	libvlc_media_release(vlcMedia);

	return Play();
}

bool VLC::Play()
{
	/* Integrate the video in the interface */
#if defined(Q_OS_MAC)
	libvlc_media_player_set_nsobject(m_pVlcPlayer, (void*)m_pWidget->winId());
#elif defined(Q_OS_UNIX)
	libvlc_media_player_set_xwindow(m_pVlcPlayer, m_pWidget->winId());
#elif defined(Q_OS_WIN)
	libvlc_media_player_set_hwnd(m_pVlcPlayer, (void*)m_pWidget->winId());
#endif

	/* And start playback */
	int vlc_ret = libvlc_media_player_play(m_pVlcPlayer);
	if (0 == vlc_ret)
		return true;
	else
		return false;
}

void VLC::Pause()
{
	if (m_pVlcPlayer && libvlc_media_player_is_playing(m_pVlcPlayer))
	{
		libvlc_media_player_pause(m_pVlcPlayer);
	}
}

void VLC::Stop()
{
	if (m_pVlcPlayer)
	{
		/* stop the media player */
		libvlc_media_player_stop(m_pVlcPlayer);

		/* release the media player */
		libvlc_media_player_release(m_pVlcPlayer);

		/* Reset application values */
		m_pVlcPlayer = NULL;
	}
}

void VLC::ChangeVolume(int vol)
{
	if (m_pVlcPlayer)
	{
		libvlc_audio_set_volume(m_pVlcPlayer, vol);
	}
}
