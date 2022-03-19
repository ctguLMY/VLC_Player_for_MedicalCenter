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

	// ���ÿ�������͸�ֵ
	VLC(const VLC&) = delete;
	VLC& operator=(VLC&) = delete;

	// Control
	virtual bool Open(const char* url);
	virtual bool Play();
	virtual void Pause();
	virtual void Stop();
	virtual void ChangeVolume(int vol);

private:
	// ����������
	libvlc_media_player_t *m_pVlcPlayer;

private:
	// libvlcʵ�������д������Ⱦ����һ��
	static libvlc_instance_t *s_pVlcInstance;
	static unsigned int s_ref;
};

