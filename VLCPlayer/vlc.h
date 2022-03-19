#pragma once
#include "IMediaPlayer.h"
struct libvlc_media_player_t;
struct libvlc_instance_t;

class VLC :
	public IMediaPlayer
{
public:
	VLC(QWidget* pWidget);
	~VLC();

	// 禁用拷贝构造和赋值
	VLC(const VLC&) = delete;
	VLC& operator=(VLC&) = delete;

	// Control
	virtual bool Open(const char* url);
	virtual bool Play();
	virtual void Pause();
	virtual void Stop();
	virtual void ChangeVolume(int vol);

private:
	// 播放器对象
	libvlc_media_player_t *m_pVlcPlayer;

private:
	// libvlc实例，所有窗体的渲染共用一个
	static libvlc_instance_t *s_pVlcInstance;
	static unsigned int s_ref;
};

