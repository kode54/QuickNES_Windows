// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "display/display.h"
#include "display/display_config.h"

#include "sound/sound_out.h"
#include "sound/sound_config.h"

#include "input/input.h"

#include "config/config.h"

#include "music/trackbar.h"

#include <zlib.h>

static int sound_buffer_frames;
static const int sound_buffer_frames_ds = 8;
static const int sound_buffer_frames_xa = 6;

/*static const int top_clip = 8; // first scanlines not visible on most televisions
static const int bottom_clip = 4; // last scanlines ^*/

void register_mappers();

#if 0
#if 1
static const unsigned char nes_palette [64][4] =
{
   {0x60,0x60,0x60}, {0x00,0x21,0x7b}, {0x00,0x00,0x9c}, {0x31,0x00,0x8b},
   {0x59,0x00,0x6f}, {0x6f,0x00,0x31}, {0x64,0x00,0x00}, {0x4f,0x11,0x00},
   {0x2f,0x19,0x00}, {0x27,0x29,0x00}, {0x00,0x44,0x00}, {0x00,0x39,0x37},
   {0x00,0x39,0x4f}, {0x00,0x00,0x00}, {0x0c,0x0c,0x0c}, {0x0c,0x0c,0x0c},
   
   {0xae,0xae,0xae}, {0x10,0x56,0xce}, {0x1b,0x2c,0xff}, {0x60,0x20,0xec},
   {0xa9,0x00,0xbf}, {0xca,0x16,0x54}, {0xca,0x1a,0x08}, {0x9e,0x3a,0x04},
   {0x67,0x51,0x00}, {0x43,0x61,0x00}, {0x00,0x7c,0x00}, {0x00,0x71,0x53},
   {0x00,0x71,0x87}, {0x0c,0x0c,0x0c}, {0x0c,0x0c,0x0c}, {0x0c,0x0c,0x0c},
   
   {0xff,0xff,0xff}, {0x44,0x9e,0xfe}, {0x5c,0x6c,0xff}, {0x99,0x66,0xff},
   {0xd7,0x60,0xff}, {0xff,0x62,0x95}, {0xff,0x64,0x53}, {0xf4,0x94,0x30},
   {0xc2,0xac,0x00}, {0x90,0xc4,0x14}, {0x52,0xd2,0x28}, {0x20,0xc6,0x92},
   {0x18,0xba,0xd2}, {0x4c,0x4c,0x4c}, {0x0c,0x0c,0x0c}, {0x0c,0x0c,0x0c},
   
   {0xff,0xff,0xff}, {0xa3,0xcc,0xff}, {0xa4,0xb4,0xff}, {0xc1,0xb6,0xff},
   {0xe0,0xb7,0xff}, {0xff,0xc0,0xc5}, {0xff,0xbc,0xab}, {0xff,0xd0,0x9f},
   {0xfc,0xe0,0x90}, {0xe2,0xea,0x98}, {0xca,0xf2,0xa0}, {0xa0,0xea,0xe2},
   {0xa0,0xe2,0xfa}, {0xb6,0xb6,0xb6}, {0x0c,0x0c,0x0c}, {0x0c,0x0c,0x0c}
};
#else
static const unsigned char nes_palette [64][4] =
{
   {0x78,0x80,0x84}, {0x00,0x00,0xfc}, {0x00,0x00,0xc4}, {0x40,0x28,0xc4},
   {0x94,0x00,0x8c}, {0xac,0x00,0x28}, {0xac,0x10,0x00}, {0x8c,0x18,0x00},
   {0x50,0x30,0x00}, {0x00,0x78,0x00}, {0x00,0x68,0x00}, {0x00,0x58,0x00},
   {0x00,0x40,0x58}, {0x00,0x00,0x00}, {0x00,0x00,0x00}, {0x00,0x00,0x08},

   {0xbc,0xc0,0xc4}, {0x00,0x78,0xfc}, {0x00,0x88,0xfc}, {0x68,0x48,0xfc},
   {0xdc,0x00,0xd4}, {0xe4,0x00,0x60}, {0xfc,0x38,0x00}, {0xe4,0x60,0x18},
   {0xac,0x80,0x00}, {0x00,0xb8,0x00}, {0x00,0xa8,0x00}, {0x00,0xa8,0x48},
   {0x00,0x88,0x94}, {0x2c,0x2c,0x2c}, {0x00,0x00,0x00}, {0x00,0x00,0x00},

   {0xfc,0xf8,0xfc}, {0x38,0xc0,0xfc}, {0x68,0x88,0xfc}, {0x9c,0x78,0xfc},
   {0xfc,0x78,0xfc}, {0xfc,0x58,0x9c}, {0xfc,0x78,0x58}, {0xfc,0xa0,0x48},
   {0xfc,0xb8,0x00}, {0xbc,0xf8,0x18}, {0x58,0xd8,0x58}, {0x58,0xf8,0x9c},
   {0x00,0xe8,0xe4}, {0x60,0x60,0x60}, {0x00,0x00,0x00}, {0x00,0x00,0x00},

   {0xfc,0xf8,0xfc}, {0xa4,0xe8,0xfc}, {0xbc,0xb8,0xfc}, {0xdc,0xb8,0xfc},
   {0xfc,0xb8,0xfc}, {0xf4,0xc0,0xe0}, {0xf4,0xc0,0xb4}, {0xfc,0xe0,0xb4},
   {0xfc,0xd8,0x84}, {0xdc,0xf8,0x78}, {0xb8,0xf8,0x78}, {0xb0,0xf0,0xd8},
   {0x00,0xf8,0xfc}, {0xc8,0xc0,0xc0}, {0x00,0x00,0x00}, {0x00,0x00,0x00}
};
#endif
#endif

static bool file_picker( HWND w, TCHAR * & path, const TCHAR * title, const TCHAR * filter, const TCHAR * default_extension, bool save )
{
	if ( ! path )
	{
#ifdef UNICODE
		path = new TCHAR[ 32768 ];
#else
		path = new TCHAR[ MAX_PATH + 1 ];
#endif
		* path = 0;
	}

	size_t filter_len = _tcslen( filter ) + 3;
	TCHAR * real_filter = new TCHAR[ filter_len ];
	memset( real_filter, 0, filter_len * sizeof( TCHAR ) );
	_tcscpy( real_filter, filter );

	for ( size_t i = 0; i < filter_len; ++i )
	{
		if ( real_filter[ i ] == _T( '|' ) ) real_filter[ i ] = 0;
	}

	OPENFILENAME ofn;
	memset( &ofn, 0, sizeof( ofn ) );

	ofn.lStructSize = sizeof( ofn );
	ofn.hwndOwner = w;
	ofn.lpstrFilter = real_filter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = path;
#ifdef UNICODE
	ofn.nMaxFile = 32767;
#else
	ofn.nMaxFile = MAX_PATH;
#endif
	ofn.lpstrTitle = title;
	ofn.lpstrDefExt = default_extension;

	if ( ! save )
	{
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

		if ( GetOpenFileName( & ofn ) )
		{
			delete [] real_filter;

			return true;
		}
	}
	else
	{
		ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

		if ( GetSaveFileName( & ofn ) )
		{
			delete [] real_filter;

			return true;
		}
	}

	delete [] real_filter;

	return false;
}

static CString format_time( unsigned seconds )
{
	std::tostringstream text;

	text << std::setw( 1 ) << std::setfill( _T( '0' ) );

	if ( seconds > 60 * 60 )
	{
		text << seconds / ( 60 * 60 ) << _T( ':' ) << std::setw( 2 )
			<< ( seconds / 60 ) % 60 << _T( ':' ) << std::setw( 2 )
			<< seconds % 60;
	}
	else
	{
		text << seconds / 60 << _T( ':' ) << std::setw( 2 )
			<< seconds % 60;
	}

	return CString( text.str().c_str() );
}

class CMainFrame : public CFrameWindowImpl<CMainFrame>, public CUpdateUI<CMainFrame>,
		public CMessageFilter, public CIdleHandler, public musicmusic::track_bar_host
{
	class bookmarks_t
	{
		unsigned bookmark[ 10 ];

	public:
		bookmarks_t()
		{
			reset();
		}

		unsigned operator [] ( unsigned n ) const
		{
			assert( n < 10 );
			return bookmark[ n ];
		}

		unsigned & operator [] ( unsigned n )
		{
			assert( n < 10 );
			return bookmark[ n ];
		}

		enum { invalid = ~0 };

		void reset()
		{
			for ( unsigned i = 0; i < ARRAYSIZE( bookmark ); ++i )
				bookmark[ i ] = invalid;
		}
	};

	bookmarks_t bookmarks;


	Nes_Recorder m_emu;
	Nes_Film     m_film;
	Nes_Cart     m_cart;

	Nes_Buffer         m_buffer;
	Nes_Effects_Buffer m_effects_buffer;

	Nes_Blitter m_blitter;

	CString save_path;

	CString path_base;
	CString filename_base;

	core_config_t core_config;

	sound_config_t sound_config;

	display_config_t display_config;

	display * m_video;

	sound_out * m_audio;

	bool skip_input_polling;

	input * m_controls;

	bool             sound_buffering;

	signed short   * sound_buf;
	unsigned         sound_buf_size;

	unsigned char * pixels;

	unsigned input_last;

	TCHAR * path;
	TCHAR * path_snap;
	TCHAR * path_film;

	CString status_text;

	enum
	{
		emu_stopped,
		emu_paused,
		emu_running
	}
	emu_state;

	int emu_speed;

	int emu_step;

	// for trackbar
	bool emu_seeking;
	bool emu_was_paused;

public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	CNes_EmuView m_view;

	CCommandBarCtrl m_CmdBar;

	musicmusic::track_bar_impl m_TrackBar;

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		if(CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
			return TRUE;

		return m_view.PreTranslateMessage(pMsg);
	}

	virtual BOOL OnIdle()
	{
		UIUpdateToolBar();
		if ( emu_state == emu_stopped )
		{
			//m_TrackBar.ClearTics();
			m_TrackBar.set_range( 0, 0 );
		}
		else if ( emu_state == emu_paused )
		{
			set_status( IDS_PAUSED );
		}
		BOOL state = emu_state != emu_stopped;
		UIEnable( ID_SNAP_LOAD, state );
		UIEnable( ID_SNAP_SAVE, state );
		UIEnable( ID_MOVIE_LOAD, state );
		UIEnable( ID_MOVIE_SAVE, state );
		UIEnable( ID_CORE_RESET, state );
		UIEnable( ID_CORE_PAUSE, state );
		UIEnable( ID_CORE_NEXTFRAME, state );
		UIEnable( ID_CORE_REWIND, state );
		UIEnable( ID_CORE_FASTFORWARD, state );
		::EnableWindow( m_TrackBar.get_wnd(), state );
		return FALSE;
	}

	BOOL IsRunning()
	{
		return ( emu_state == emu_running ) ? TRUE : FALSE;
	}

	void set_status( int nID )
	{
		CString text;
		text.LoadString( nID );
		if ( status_text != text )
		{
			CStatusBarCtrl status = m_hWndStatusBar;
			status.SetText( 0, status_text = text );
		}
	}

	void config_sound()
	{
		Nes_Emu::equalizer_t eq = Nes_Emu::tv_eq;
		if ( sound_config.effects_enabled )
		{
			// bass - logarithmic, 2 to 8194 Hz
			double bass = double( 255 - sound_config.bass ) / 255;
			eq.bass = std::pow( 2.0, bass * 13 ) + 2.0;

			// treble - level from -108 to 0 to 5 dB
			double treble = double( sound_config.treble - 128 ) / 128;
			eq.treble = treble * ( ( treble > 0 ) ? 16.0 : 80.0 ) - 8.0;
		}
		m_emu.set_equalizer( eq );

		double depth = double( sound_config.echo_depth ) / 255;
		Effects_Buffer::config_t cfg;
		cfg.pan_1 = -0.6 * depth;
		cfg.pan_2 = 0.6 * depth;
		cfg.reverb_delay = 880 * 0.1;
		cfg.reverb_level = 0.5 * depth;
		cfg.echo_delay = 610 * 0.1;
		cfg.echo_level = 0.30 * depth;
		cfg.delay_variance = 180 * 0.1;
		cfg.effects_enabled = ( ( sound_config.effects_enabled ) && ( sound_config.echo_depth > 0 ) );
		m_effects_buffer.config( cfg );
	}

	LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if ( emu_state == emu_paused )
		{
			if ( m_controls )
			{
				m_controls->poll();

				emu_speed = m_controls->get_speed();

				if ( emu_speed )
				{
					BOOL unused;
					OnCorePause(0, 0, 0, unused);
				}

				skip_input_polling = true;
			}
		}
		else KillTimer( 0 );

		return 0;
	}

	void DoFrame()
	{
		if ( emu_state == emu_running )
		{
			const char * err = 0;

			BOOL cut = FALSE;

			if ( ! m_audio )
			{
				//sound_buf_size = sound_config.sample_rate / ( m_emu.frame_rate / 2 ) * 2;
				sound_buf_size = sound_config.sample_rate / m_emu.frame_rate * ( sound_config.effects_enabled ? 2 : 1 );

				m_audio = create_sound_out_xaudio2();
				err = m_audio->open( m_hWnd, sound_config.sample_rate, sound_config.effects_enabled ? 2 : 1, sound_buf_size, sound_buffer_frames = sound_buffer_frames_xa );
				if ( err )
				{
					delete m_audio;
					m_audio = create_sound_out_ds();
					err = m_audio->open( m_hWnd, sound_config.sample_rate, sound_config.effects_enabled ? 2 : 1, sound_buf_size, sound_buffer_frames = sound_buffer_frames_ds );
				}
				if ( ! err )
				{
					if ( sound_config.effects_enabled ) err = m_emu.set_sample_rate( sound_config.sample_rate, &m_effects_buffer );
					else err = m_emu.set_sample_rate( sound_config.sample_rate, &m_buffer );
				}
				if ( err )
				{
					stop_error( err );
					return;
				}

				config_sound();

				if ( sound_buf )
				{
					delete [] sound_buf;
					sound_buf = 0;
				}

				sound_buf = new short[ sound_buf_size ];

				sound_buffering = true;
			}

			unsigned input_now = 0;

			if ( m_controls )
			{
				if ( !skip_input_polling ) m_controls->poll();
				skip_input_polling = false;

				emu_speed = m_controls->get_speed();

				input_now = m_controls->read();

				if ( input_now != input_last )
				{
					unsigned change = input_now ^ input_last;
					if ( input_now & change )
					{
						m_emu.film().trim( m_emu.film().begin(), m_emu.tell() );
					}

					input_last = input_now;
				}

				if ( !emu_seeking && ( emu_speed == 0 || ( emu_speed < 0 && m_emu.tell() <= m_emu.film().begin() ) ) )
				{
					BOOL unused;
					if ( emu_speed == 0 ) OnCorePause(0, 0, 0, unused);
					set_status( IDS_PAUSED );
					return;
				}
			}

			if ( m_video )
			{
				if ( !core_config.record_indefinitely && !m_film.blank() )
				{
					long begin = m_film.constrain( m_film.end() - 5 * 60 * m_emu.frame_rate );
					if ( emu_speed < 0 && m_emu.tell() <= begin )
					{
						m_emu.seek( begin );
						set_status( IDS_PAUSED );
						return;
					}
					m_film.trim( begin, m_film.end() );
				}

				int dir = emu_speed >= 0 ? 1 : -1;
				if ( ! emu_seeking ) dir = emu_speed;
				while ( dir )
				{
					if ( dir < 0 && m_emu.tell() <= m_film.begin() )
					{
						set_status( IDS_PAUSED );
						return;
					}

					if ( dir < 0 )
						m_emu.prev_frame();
					else if ( m_emu.tell() < m_emu.film().end() )
						m_emu.next_frame();
					else
					{
						err = m_emu.emulate_frame( input_now & 255, ( input_now >> 8 ) & 255 );
						if ( err )
						{
							stop_error( err );
							return;
						}
					}

					if ( m_controls && m_emu.frame().joypad_read_count > 0 )
						m_controls->strobe();

					dir += ( dir < 0 ? 1 : -1 );

					if ( m_controls && dir )
					{
						m_controls->poll();
						input_now = m_controls->read();
					}
				}

				if ( m_audio && ! emu_seeking )
				{
					unsigned samples_read = m_emu.read_samples( sound_buf, sound_buf_size );
					err = m_audio->write_frame( sound_buf, samples_read );
					if ( err )
					{
						stop_error( err );
						return;
					}
					double buffered = m_audio->buffered();
					if ( buffered <= 1.0 ) sound_buffering = true;
					else if ( sound_buffering && ( sound_buffer_frames - buffered ) < 1.0 ) sound_buffering = false;
					if ( !sound_buffering && !! display_config.vsync )
					{
						double ratio;
						double sound_buffer_frame_threshold = sound_buffer_frames - 1;
						if ( buffered >= sound_buffer_frame_threshold ) ratio = 1.0 + ( ( buffered - sound_buffer_frame_threshold ) * 0.01 );
						else ratio = 1.0 - ( ( sound_buffer_frame_threshold - buffered ) / sound_buffer_frame_threshold * 0.01 );
						m_audio->set_ratio( ratio );
#if 0
						char temp[64];
						_snprintf( temp, 63, "%1.6f - %1.6f\n", buffered, ratio );
						temp[ 63 ] = 0;
						OutputDebugStringA( temp );
#endif
					}
					else m_audio->set_ratio( 1.0 );
#if 0
					if ( sound_buffering ) OutputDebugStringA( "Buffering\n" );
#endif
				}
				else sound_buffering = false;

				if ( !sound_buffering )
				{
					void * fb;
					unsigned pitch;
					err = m_video->lock_framebuffer( fb, pitch );
					if ( ! err )
					{
						m_blitter.blit( m_emu, fb, pitch );
						m_video->unlock_framebuffer();
					}

					/*RECT rect;

					{
					const Nes_Emu::frame_t & frame = m_emu.frame();
					m_video->update_palette( ( const unsigned char * ) & nes_palette, frame.palette, frame.palette_begin, frame.palette_size );

					rect.left = frame.left;
					rect.top = frame.top + top_clip;
					}

					rect.right = rect.left + m_emu.image_width;
					rect.bottom = rect.top + m_emu.image_height - top_clip - bottom_clip;*/

					bool wait_for_vsync = !! display_config.vsync;

					m_video->paint( /*rect,*/ wait_for_vsync );
				}
			}

			if ( ! emu_seeking )
			{
				m_TrackBar.set_range( m_emu.film().begin(), m_emu.film().end() );
				m_TrackBar.set_position( m_emu.tell() );
			}
			UISetCheck( ID_CORE_REWIND, emu_speed < 0 );
			UISetCheck( ID_CORE_FASTFORWARD, emu_speed > 1 );

			set_status( emu_speed < 0 ? IDS_REWINDING : ( ( m_emu.tell() < m_emu.film().end() ) ? IDS_PLAYING : IDS_RECORDING ) );

			if ( emu_step )
			{
				if ( --emu_step == 0 )
				{
					emu_state = emu_paused;
					if ( !emu_seeking )
					{
						if ( m_controls ) m_controls->set_paused( true );
						SetTimer( 0, 10 );
					}
				}
			}
		}
	}

	BEGIN_UPDATE_UI_MAP(CMainFrame)
		//UPDATE_ELEMENT(ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_SNAP_LOAD, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_SNAP_SAVE, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_MOVIE_LOAD, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_MOVIE_SAVE, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_CORE_RESET, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_CORE_PAUSE, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_CORE_NEXTFRAME, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_CORE_REWIND, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_CORE_FASTFORWARD, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_CORE_RECORDINDEFINITELY, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		//MESSAGE_HANDLER(WM_SIZING, OnSizing)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		MESSAGE_HANDLER(WM_MOVE, OnMove)
		MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
		COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
		COMMAND_ID_HANDLER(ID_FILE_OPEN, OnFileOpen)
		COMMAND_ID_HANDLER(ID_SNAP_LOAD, OnSnapLoad)
		COMMAND_ID_HANDLER(ID_SNAP_SAVE, OnSnapSave)
		COMMAND_ID_HANDLER(ID_MOVIE_LOAD, OnMovieLoad)
		COMMAND_ID_HANDLER(ID_MOVIE_SAVE, OnMovieSave)
		COMMAND_ID_HANDLER(ID_SNAP_LOAD_0, OnSnapLoad_Q0)
		COMMAND_ID_HANDLER(ID_SNAP_LOAD_1, OnSnapLoad_Q1)
		COMMAND_ID_HANDLER(ID_SNAP_LOAD_2, OnSnapLoad_Q2)
		COMMAND_ID_HANDLER(ID_SNAP_LOAD_3, OnSnapLoad_Q3)
		COMMAND_ID_HANDLER(ID_SNAP_LOAD_4, OnSnapLoad_Q4)
		COMMAND_ID_HANDLER(ID_SNAP_LOAD_5, OnSnapLoad_Q5)
		COMMAND_ID_HANDLER(ID_SNAP_LOAD_6, OnSnapLoad_Q6)
		COMMAND_ID_HANDLER(ID_SNAP_LOAD_7, OnSnapLoad_Q7)
		COMMAND_ID_HANDLER(ID_SNAP_LOAD_8, OnSnapLoad_Q8)
		COMMAND_ID_HANDLER(ID_SNAP_LOAD_9, OnSnapLoad_Q9)
		COMMAND_ID_HANDLER(ID_SNAP_SAVE_0, OnSnapSave_Q0)
		COMMAND_ID_HANDLER(ID_SNAP_SAVE_1, OnSnapSave_Q1)
		COMMAND_ID_HANDLER(ID_SNAP_SAVE_2, OnSnapSave_Q2)
		COMMAND_ID_HANDLER(ID_SNAP_SAVE_3, OnSnapSave_Q3)
		COMMAND_ID_HANDLER(ID_SNAP_SAVE_4, OnSnapSave_Q4)
		COMMAND_ID_HANDLER(ID_SNAP_SAVE_5, OnSnapSave_Q5)
		COMMAND_ID_HANDLER(ID_SNAP_SAVE_6, OnSnapSave_Q6)
		COMMAND_ID_HANDLER(ID_SNAP_SAVE_7, OnSnapSave_Q7)
		COMMAND_ID_HANDLER(ID_SNAP_SAVE_8, OnSnapSave_Q8)
		COMMAND_ID_HANDLER(ID_SNAP_SAVE_9, OnSnapSave_Q9)
		COMMAND_ID_HANDLER(ID_CORE_RESET, OnCoreReset)
		COMMAND_ID_HANDLER(ID_CORE_PAUSE, OnCorePause)
		COMMAND_ID_HANDLER(ID_CORE_NEXTFRAME, OnCoreNextFrame)
		COMMAND_ID_HANDLER(ID_CORE_REWIND, OnCoreRewind)
		COMMAND_ID_HANDLER(ID_CORE_FASTFORWARD, OnCoreFastForward)
		COMMAND_ID_HANDLER(ID_CORE_RECORDINDEFINITELY, OnCoreRecordIndefinitely)
		COMMAND_ID_HANDLER(ID_CONFIGUREINPUT, OnConfigureInput)
		COMMAND_ID_HANDLER(ID_CONFIGURESOUND, OnConfigureSound)
		COMMAND_ID_HANDLER(ID_CONFIGUREDISPLAY, OnConfigureDisplay)
		COMMAND_ID_HANDLER(ID_VIEW_STATUS_BAR, OnViewStatusBar)
		COMMAND_ID_HANDLER(ID_HELP_CONTROLS, OnHelpControls)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
	CMainFrame()
	{
		m_video = 0;

		m_audio = 0;

		m_controls = 0;

		sound_buf = 0;

		pixels = 0;

		emu_state = emu_stopped;

		emu_seeking = false;
		
		path = 0;
		path_snap = 0;
		path_film = 0;

		m_film.clear( 30 * m_emu.frame_rate );

		const char * err = m_emu.set_sample_rate( 44100, &m_buffer );

		if ( ! err )
		{
			m_emu.set_film( & m_film );

			pixels = new unsigned char [(m_emu.buffer_height() + 1) * m_emu.buffer_width];
			if ( pixels )
				m_emu.set_pixels( pixels, m_emu.buffer_width );
		}
	}

	~CMainFrame()
	{
		m_TrackBar.destroy();

		if ( filename_base.GetLength() )
		{
			sram_save();
			filename_base.Empty();
			path_base.Empty();
		}

		if ( m_controls )
		{
			input_config_save();

			delete m_controls;
			m_controls = 0;
		}

		if ( m_audio )
		{
			delete m_audio;
			m_audio = 0;
		}

		if ( m_video )
		{
			delete m_video;
			m_video = 0;
		}

		if ( sound_buf )
		{
			delete [] sound_buf;
			sound_buf = 0;
		}

		if ( pixels )
		{
			delete [] pixels;
			pixels = 0;
		}

		if ( path_film )
		{
			delete [] path_film;
			path_film = 0;
		}

		if ( path_snap )
		{
			delete [] path_snap;
			path_snap = 0;
		}

		if ( path )
		{
			delete [] path;
			path = 0;
		}

		if ( save_path.GetLength() )
		{
			core_config_save( core_config, save_path );
			sound_config_save( sound_config, save_path );
			display_config_save( display_config, save_path );
		}
	}

	bool init_save_path()
	{
		TCHAR path[ MAX_PATH + 1 ];
		if ( SUCCEEDED( SHGetFolderPath( 0, CSIDL_APPDATA | CSIDL_FLAG_CREATE, 0, SHGFP_TYPE_CURRENT, path ) ) )
		{
			save_path = path;
			save_path += _T( "\\QuickNES" );
			if ( CreateDirectory( save_path, NULL ) || GetLastError() == ERROR_ALREADY_EXISTS )
			{
				save_path += _T( '\\' );
				CString temp = save_path + _T( "snap" );
				if ( CreateDirectory( temp, NULL ) || GetLastError() == ERROR_ALREADY_EXISTS )
				{
					temp = save_path + _T( "sram" );
					if ( CreateDirectory( temp, NULL ) || GetLastError() == ERROR_ALREADY_EXISTS )
					{
						core_config_load( core_config, save_path );
						sound_config_load( sound_config, save_path );
						display_config_load( display_config, save_path );

						return true;
					}
				}
			}
		}

		save_path.Empty();

		return false;
	}

	void input_config_load()
	{
		CString temp = save_path + _T( "input.cfg" );
		Gzip_File_Reader_u in;
		if ( ! in.open( temp ) )
		{
			m_controls->load( in );
		}
	}

	void input_config_save()
	{
		CString temp = save_path + _T( "input.cfg" );
		Gzip_File_Writer_u out;
		if ( ! out.open( temp ) )
		{
			m_controls->save( out );
		}
	}

	/*void update_bookmarks()
	{
		m_TrackBar.ClearTics( TRUE );
		for ( unsigned i = 0; i < 10; ++i )
		{
			if ( bookmarks[ i ] != bookmarks_t::invalid )
				m_TrackBar.SetTic( bookmarks[ i ] );
		}
	}*/

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// create command bar window
		HWND hWndCmdBar = m_CmdBar.Create( m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE );
		m_CmdBar.m_bFlatMenus = false;
		// attach menu
		m_CmdBar.AttachMenu( GetMenu() );
		// load command bar images
		//m_CmdBar.LoadImages(IDR_MAINFRAME);
		// remove old menu
		SetMenu( NULL );

		//HWND hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);

		//HWND hWndTrackBar = m_TrackBar.Create( m_hWnd, WTL::CRect( 0, 0, 120, 18 ), NULL, WS_CHILD | WS_VISIBLE | TBS_BOTTOM | TBS_HORZ );
		m_TrackBar.create( m_hWnd );
		::EnableWindow( m_TrackBar.get_wnd(), FALSE );

		m_TrackBar.set_callback( this );
		m_TrackBar.set_show_tooltips( true );
		::SetWindowPos( m_TrackBar.get_wnd(), NULL, 0, 0, 120, 18, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOMOVE );

		CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
		AddSimpleReBarBand(hWndCmdBar);
		AddSimpleReBarBand(m_TrackBar.get_wnd());

		CReBarCtrl rebar = m_hWndToolBar;
		rebar.LockBands( true );
		int width = GetSystemMetrics( SM_CXFRAME );
		for ( int i = 0, j = m_CmdBar.GetButtonCount(); i < j; i++ )
		{
			RECT r;
			m_CmdBar.GetItemRect( i, &r );
			width += r.right - r.left;
		}
		REBARBANDINFO bandinfo;
		memset( &bandinfo, 0, sizeof( bandinfo ) );
		bandinfo.cbSize = sizeof( bandinfo );
		bandinfo.fMask = RBBIM_SIZE;
		rebar.GetBandInfo( 0, &bandinfo );
		bandinfo.cx = width;
		rebar.SetBandInfo( 0, &bandinfo );
		rebar.Detach();

		// m_CmdBar.Prepare();

		CreateSimpleStatusBar( ATL_IDS_IDLEMESSAGE, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS );

		status_text.Empty();

		m_hWndClient = m_view.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);

		if ( ! init_save_path() )
		{
			CString error, message;
			error.LoadString( IDS_ERROR );
			message.LoadString( IDS_ERROR_CONFIG );
			MessageBox( message, error, MB_ICONERROR | MB_OK );
			PostMessage( WM_CLOSE );
			return 0;
		}

		if ( core_config.record_indefinitely )
			UISetCheck( ID_CORE_RECORDINDEFINITELY, 1 );

		if ( core_config.show_status_bar )
		{
			BOOL handled;
			OnViewStatusBar( 0, 0, 0, handled );
		}

		/*SetWindowPos( NULL, 0, 0, 640, 456, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOMOVE );
		RECT rcClient;
		m_view.GetClientRect( & rcClient );
		SetWindowPos( NULL, 0, 0, 640 + ( 640 - rcClient.right - rcClient.left ), 456 + ( 456 - rcClient.bottom - rcClient.top ), SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOMOVE );*/

		const char * err = m_blitter.init();

		if ( !err )
		{
			m_video = create_display_d2d();
			err = m_video->open( m_blitter.out_width(), m_blitter.out_height(), m_hWndClient );
			if ( err )
			{
				delete m_video;
				m_video = create_display_d3d9();
				//err = m_video->open( m_emu.buffer_width, m_emu.buffer_height(), m_hWndClient );
				err = m_video->open( m_blitter.out_width(), m_blitter.out_height(), m_hWndClient );
			}
		}

		if ( err )
		{
			delete m_video;
			m_video = 0;
			CString error;
			error.LoadString( IDS_ERROR );
			MessageBox( CString( err ), error , MB_ICONERROR | MB_OK );
			PostMessage( WM_CLOSE );
			return 0;
		}

		m_controls = create_input();
		err = m_controls->open( ATL::_AtlBaseModule.GetModuleInstance(), m_hWnd );
		if ( err )
		{
			delete m_controls;
			m_controls = 0;
			stop_error( err );
		}
		else input_config_load();

		m_view.m_video = m_video;

		register_mappers();

#ifndef _DEBUG
		::SetPriorityClass( ::GetCurrentProcess(), HIGH_PRIORITY_CLASS );
		::SetThreadPriority( ::GetCurrentThread(), THREAD_PRIORITY_HIGHEST );
#endif

		// register object for message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);

		return 0;
	}

	void UpdateLayout(BOOL bResizeBars = TRUE)
	{
		RECT rcw, rcc, rcs;
		GetClientRect( & rcw );

		rcc = rcw;

		// position bars and offset their dimensions
		UpdateBarsPosition( rcc, bResizeBars );

		rcs.left = 0;
		rcs.top = 0;
		rcs.right = m_blitter.rescale_width();
		rcs.bottom = m_blitter.out_height() * 2;

		if ( m_hWndClient != NULL )
		{
			CWindow client = m_hWndClient;
			::AdjustWindowRectEx( & rcs, client.GetStyle(), FALSE, client.GetExStyle() );
		}

		rcw.right += ( rcs.right - rcs.left ) - ( rcc.right - rcc.left );
		rcw.bottom += ( rcs.bottom - rcs.top ) - ( rcc.bottom - rcc.top );

		::AdjustWindowRectEx( & rcw, GetStyle(), FALSE, GetExStyle() );

		SetWindowPos( NULL, 0, 0, rcw.right - rcw.left, rcw.bottom - rcw.top, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOMOVE );

		CFrameWindowImpl<CMainFrame>::UpdateLayout( bResizeBars );

		if ( m_video ) m_video->update_position();
	}

	LRESULT OnMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if ( m_video ) m_video->update_position();

		return 0;
	}

	LRESULT OnSetFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if ( m_controls ) m_controls->set_focus( true );

		return 0;
	}

	LRESULT OnKillFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if ( m_controls ) m_controls->set_focus( false );

		return 0;
	}

	virtual void on_position_change( unsigned pos, bool b_tracking )
	{
		if ( emu_state != emu_stopped )
		{
			if ( b_tracking )
			{
				if ( ! emu_seeking )
				{
					emu_seeking = true;
					emu_was_paused = emu_state == emu_paused;
				}

				m_emu.seek( m_emu.nearby_keyframe( m_emu.film().constrain( pos ) ) );
				emu_state = emu_running;
				emu_step = 1;
			}
			else
			{
				if ( emu_seeking )
				{
					emu_seeking = false;
					emu_state = emu_was_paused ? emu_paused : emu_running;
				}

				m_emu.seek( m_emu.nearby_keyframe( m_emu.film().constrain( pos ) ) );
				emu_step = 0;
			}
		}
	}

	virtual void get_tooltip_text(unsigned pos, CString & p_out)
	{
		p_out = format_time( pos / m_emu.frame_rate );
	}

#if 0
	LRESULT OnSizing(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		RECT & r = * ( RECT * ) lParam;

		RECT rcClient;
		m_view.GetClientRect( & rcClient );

		int width = rcClient.right - rcClient.left;
		int height = rcClient.bottom - rcClient.top;

		int newwidth = ( height * 256 / 228 ) - width;
		int newheight = ( width * 228 / 256 ) - height;

		if ( ! newwidth && ! newheight ) return 0;

		switch ( wParam )
		{
		case WMSZ_TOP:
		case WMSZ_BOTTOM:
			r.left -= newwidth / 2;
			r.right += newwidth / 2;
			break;

		case WMSZ_LEFT:
		case WMSZ_RIGHT:
			r.top -= newheight / 2;
			r.bottom += newheight / 2;
			break;

		case WMSZ_TOPLEFT:
			if ( newwidth < 0 )
				r.top -= newheight;
			else
				r.left -= newwidth;
			break;

		case WMSZ_TOPRIGHT:
			if ( newwidth < 0 )
				r.top -= newheight;
			else
				r.right += newwidth;
			break;

		case WMSZ_BOTTOMLEFT:
			if ( newwidth < 0 )
				r.bottom += newheight;
			else
				r.left -= newwidth;
			break;

		case WMSZ_BOTTOMRIGHT:
			if ( newwidth < 0 )
				r.bottom += newheight;
			else
				r.right += newwidth;
			break;
		}

		return TRUE;
	}
#endif

	LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		PostMessage(WM_CLOSE);
		return 0;
	}

	void stop_error( const char * err )
	{
		emu_state = emu_stopped;
		CStatusBarCtrl status = m_hWndStatusBar;
		status.SetText( 0, CString( err ) );
		status_text.Empty();

		if ( m_audio )
		{
			delete m_audio;
			m_audio = 0;
		}

		if ( m_video )
		{
			m_video->clear();
		}

		filename_base.Empty();
		path_base.Empty();
	}

	LRESULT OnFileOpen(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CString title, filter, extension;
		title.LoadString( IDS_CART_TITLE );
		filter.LoadString( IDS_CART_FILTER );
		extension.LoadString( IDS_CART_EXTENSION );
		if ( file_picker( m_hWnd, path, title, filter, extension, false ) )
		{
			emu_speed = 1;
			emu_step = 0;
			emu_seeking = false;
			emu_was_paused = false;
			UISetCheck( ID_CORE_PAUSE, 0 );
			UISetCheck( ID_CORE_REWIND, 0 );
			UISetCheck( ID_CORE_FASTFORWARD, 0 );

			if ( m_audio )
			{
				delete m_audio;
				m_audio = 0;
			}

			input_last = 0;
			if ( m_controls ) m_controls->reset();

			if ( filename_base.GetLength() )
			{
				sram_save();
				filename_base.Empty();
				path_base.Empty();
			}

			bookmarks.reset();
			//m_TrackBar.ClearTics( TRUE );

			//Multi_Buffer * buffer = sound_config.effects_enabled ? ( ( Multi_Buffer * ) &m_effects_buffer ) : ( ( Multi_Buffer * ) &m_buffer );

			m_emu.close();
			m_cart.clear();
			m_film.clear( 30 * m_emu.frame_rate );

			bool is_ines = false;
			bool is_zapfc = false;

			TCHAR * ext = _tcsrchr( path, _T( '.' ) );
			if ( ext )
			{
				if ( !_tcsicmp( ext + 1, _T( "nes" ) ) ) is_ines = true;
				else
				{
					*ext = 0;
					TCHAR * ext2 = _tcsrchr( path, _T( '.' ) );
					if ( ext2 && !_tcsicmp( ext2 + 1, _T( "fc" ) ) ) is_zapfc = true;
					*ext = _T( '.' );
				}
			}

			wchar_t * board = NULL;

			fex_t * in = NULL;
#ifdef _UNICODE
			char * path8 = fex_wide_to_path( path );
			const char * err = fex_open( &in, path8 );
			fex_free_path( path8 );
#else
			const char * err = fex_open( &in, path );
#endif
			if ( ! err )
			{
				const TCHAR * root = _tcsrchr( path, _T( '\\' ) );
				if ( ! root ) root = path;
				else root += 1;
				filename_base = root;
				if ( root > path ) path_base = CString( path, root - path );
				else path_base = _T( "" );
				int dot = filename_base.ReverseFind( _T( '.' ) );
				if ( dot >= 0 )
				{
					filename_base = filename_base.Left( dot );
					if ( is_zapfc ) filename_base = filename_base.Left( filename_base.ReverseFind( _T( '.' ) ) );
				}
			}
			if ( ! err )
			{
				if ( is_zapfc )
				{
					fex_pos_t prg_pos = 0;
					fex_pos_t chr_pos = 0;
					fex_pos_t board_pos = 0;

					while ( !fex_done( in ) )
					{
						const char * name = fex_name( in );
						if ( !stricmp( name, "prg" ) ) prg_pos = fex_tell_arc( in );
						else if ( !stricmp( name, "chr" ) ) chr_pos = fex_tell_arc( in );
						else if ( !stricmp( name, "board" ) ) board_pos = fex_tell_arc( in );
						else
						{
							err = "Invalid ZapFC archive";
							break;
						}
						err = fex_next( in );
						if ( err ) break;
					}

					if ( !err )
					{
						do
						{
							if ( !prg_pos )
							{
								err = "Invalid ZapFC archive";
								break;
							}
							else
							{
								err = fex_seek_arc( in, prg_pos );
								if ( err ) break;
								err = fex_stat( in );
								if ( err ) break;

								unsigned prg_size = fex_size( in );
								err = m_cart.resize_prg( prg_size );
								if ( err ) break;
								err = fex_read( in, m_cart.prg(), prg_size );
								if ( err ) break;

								if ( chr_pos )
								{
									err = fex_seek_arc( in, chr_pos );
									if ( err ) break;
									err = fex_stat( in );
									if ( err ) break;

									unsigned chr_size = fex_size( in );
									err = m_cart.resize_chr( chr_size );
									if ( err ) break;
									err = fex_read( in, m_cart.chr(), chr_size );
									if ( err ) break;
								}

								if ( board_pos )
								{
									err = fex_seek_arc( in, board_pos );
									if ( err ) break;
									err = fex_stat( in );
									if ( err ) break;

									unsigned board_size = fex_size( in );
									char * board8 = new char[ board_size + 1 ];
									board8[ board_size ] = 0;
									err = fex_read( in, board8, board_size );
									if ( err ) break;

									board = blargg_to_wide( board8 );
									if ( !board )
									{
										err = "Out of memory";
										break;
									}
								}
								else
								{
									board = database_lookup( m_cart.prg(), m_cart.prg_size(), m_cart.chr(), m_cart.chr_size(), save_path );
									if ( !board )
									{
										err = "Database lookup failure";
										break;
									}
								}
							}
						}
						while ( 0 );
					}
				}
				else
				{
					fex_pos_t ines_pos = 0;
					fex_pos_t ips_pos = 0;
					while ( !fex_done( in ) )
					{
						const char * name = fex_name( in );
						size_t length = strlen( name );
						if ( !ines_pos && length >= 4 && !_stricmp( name + length - 4, ".nes" ) ) ines_pos = fex_tell_arc( in );
						else if ( !ips_pos && length >= 4 && !_stricmp( name + length - 4, ".ips" ) ) ips_pos = fex_tell_arc( in );
						if ( ines_pos && ips_pos ) break;
						err = fex_next( in );
						if ( err ) break;
					}

					do
					{
						if ( !ines_pos )
						{
							err = "Archive does not contain any iNES files";
							break;
						}

						void * ips_data = NULL;
						Data_Reader * ips_reader = NULL;
						if ( is_ines && !ips_pos )
						{
							WTL::CString ips_name = path_base + filename_base + _T( ".ips" );
							Std_File_Reader_u * reader = new Std_File_Reader_u;
							err = reader->open( ips_name );
							if ( err )
							{
								delete reader;
								err = 0;
							}
							else
							{
								ips_reader = reader;
							}
						}
						else if ( ips_pos )
						{
							err = fex_seek_arc( in, ips_pos );
							if ( err ) break;
							const void * temp;
							err = fex_data( in, &temp );
							if ( err ) break;
							unsigned ips_size = fex_size( in );
							ips_data = malloc( ips_size );
							if ( !ips_size )
							{
								err = "Out of memory";
								break;
							}
							memcpy( ips_data, temp, ips_size );
							ips_reader = new Mem_File_Reader( ips_data, ips_size );
						}

						err = fex_seek_arc( in, ines_pos );
						if ( err )
						{
							delete ips_reader;
							if ( ips_data ) free( ips_data );
							break;
						}
						const void * ines_data;
						err = fex_data( in, &ines_data );
						if ( err )
						{
							delete ips_reader;
							if ( ips_data ) free( ips_data );
							break;
						}

						if ( ips_reader ) err = m_cart.load_patched_ines( Mem_File_Reader( ines_data, fex_size( in ) ), *ips_reader );
						else err = m_cart.load_ines( Mem_File_Reader( ines_data, fex_size( in ) ) );

						delete ips_reader;
						if ( ips_data ) free( ips_data );
					}
					while ( 0 );
				}
			}
			fex_close( in );
			in = NULL;
			if ( ! err && is_zapfc )
			{
				WTL::CString ips_path = path_base + filename_base + ".ips.*";
				WTL::CFindFile find;
				if ( find.FindFile( ips_path ) )
				{
					do
					{
						if ( !find.IsDirectory() )
						{
							WTL::CString ips_file = find.GetFilePath();
#ifdef _UNICODE
							char * path8 = fex_wide_to_path( ips_file );
							err = fex_open( &in, path8 );
							fex_free_path( path8 );
#else
							err = fex_open( &in, ips_file );
#endif
							if ( err ) break;

							fex_pos_t ips_prg_pos = 0;
							fex_pos_t ips_chr_pos = 0;

							while ( !fex_done( in ) )
							{
								const char * name = fex_name( in );
								if ( !_stricmp( name, "prg.ips" ) ) ips_prg_pos = fex_tell_arc( in );
								else if ( !_stricmp( name, "chr.ips" ) ) ips_chr_pos = fex_tell_arc( in );
								err = fex_next( in );
								if ( err ) break;
							}

							if ( err ) break;

							if ( ips_prg_pos )
							{
								err = fex_seek_arc( in, ips_prg_pos );
								if ( err ) break;
								err = fex_stat( in );
								if ( err ) break;

								const void * ips_data;
								err = fex_data( in, &ips_data );
								if ( err ) break;

								err = m_cart.apply_ips_to_prg( Mem_File_Reader( ips_data, fex_size( in ) ) );
								if ( err ) break;
							}

							if ( ips_chr_pos )
							{
								err = fex_seek_arc( in, ips_chr_pos );
								if ( err ) break;
								err = fex_stat( in );
								if ( err ) break;

								const void * ips_data;
								err = fex_data( in, &ips_data );
								if ( err ) break;

								err = m_cart.apply_ips_to_chr( Mem_File_Reader( ips_data, fex_size( in ) ) );
								if ( err ) break;
							}

							break;
						}
					}
					while ( find.FindNextFile() );
				}
			}
			if ( ! err && !is_zapfc )
			{
				// Board overrides from the ZapFC database
				board = database_lookup( m_cart.prg(), m_cart.prg_size(), m_cart.chr(), m_cart.chr_size(), save_path );
			}
			if ( board )
			{
				do
				{
					wchar_t * rom_filename = board;
					wchar_t * rom_size = wcschr( rom_filename, 0x2588 );
					if ( !rom_size ) break;
					*rom_size++ = 0;
					wchar_t * rom_hash = wcschr( rom_size, 0x2588 );
					if ( !rom_hash ) break;
					*rom_hash++ = 0;
					wchar_t * board_name = wcschr( rom_hash, 0x2588 );
					if ( !board_name ) break;
					*board_name++ = 0;
					wchar_t * board_type = wcschr( board_name, 0x2588 );
					if ( !board_type ) break;
					*board_type++ = 0;
					wchar_t * mirroring = wcschr( board_type, 0x2588 );
					if ( !mirroring ) break;
					*mirroring++ = 0;
					wchar_t * wram = wcschr( mirroring, 0x2588 );
					if ( !wram ) break;
					*wram++ = 0;
					wchar_t * vram_size = wcschr( wram, 0x2588 );
					if ( !vram_size ) break;
					*vram_size++ = 0;
					wchar_t * lockout_chip = wcschr( vram_size, 0x2588 );
					if ( !lockout_chip ) break;
					*lockout_chip++ = 0;
					wchar_t * mappers = wcschr( lockout_chip, 0x2588 );
					if ( !mappers ) break;
					*mappers++ = 0;
					wchar_t * eol = wcschr( mappers, 0x2588 );
					if ( eol ) *eol = 0;

					wchar_t * end_ptr;
					unsigned mapper_number = wcstoul( board_type, &end_ptr, 10 );

					unsigned mirroring_bits = 0;
					if ( !_wcsicmp( mirroring, _T( "Vertical" ) ) ) mirroring_bits = 1;

					unsigned wram_bits = 0;
					if ( wcschr( wram, _T( '*' ) ) ) wram_bits = 2;

					m_cart.set_mapper( mirroring_bits + wram_bits + ( mapper_number & 0x0F ) * 0x10, mapper_number & 0xF0 );
				}
				while ( 0 );

				free( board );
				board = NULL;
			}
			if ( ! err ) err = m_emu.set_cart( & m_cart );
			//if ( ! err && ! core_config.record_indefinitely ) err = m_emu.film().make_circular( 5 * 60 * m_emu.frame_rate );
			//if ( ! err ) err = m_emu.set_sample_rate( sound_config.sample_rate, buffer );
			if ( ! err )
			{
				emu_state = emu_running;
				skip_input_polling = false;
				sram_load();
			}

			if ( err ) stop_error( err );
		}

		return 0;
	}

	void sram_load()
	{
		CString temp = save_path + _T( "sram" ) + _T( '\\' ) + filename_base + _T( ".sav" );
		Gzip_File_Reader_u in;
		if ( ! in.open( temp ) )
		{
			m_emu.load_battery_ram( in );
		}
	}

	void sram_save()
	{
		CString temp = save_path + _T( "sram" ) + _T( '\\' ) + filename_base + _T( ".sav" );

		if ( m_emu.has_battery_ram() )
		{
			Gzip_File_Writer_u out;
			if ( ! out.open( temp ) )
			{
				m_emu.save_battery_ram( out );
				return;
			}
		}

		_tremove( temp );
	}

	void snap_load( const TCHAR * path )
	{
		Gzip_File_Reader_u in;
		const char * err = in.open( path );
		if ( ! err )
		{
			Nes_Film & film = m_emu.film();

			err = film.read( in );
			if ( ! err )
			{
				m_emu.set_film( & film, film.end() );
				input_last = 0;
				if ( m_controls ) m_controls->reset();
			}

			if ( err ) stop_error( err );
		}
	}

	void snap_load( unsigned snap )
	{
		if ( bookmarks[ snap ] != bookmarks_t::invalid )
		{
			if ( bookmarks[ snap ] >= m_emu.film().begin() &&
				bookmarks[ snap ] <= m_emu.film().end() )
				m_emu.seek( bookmarks[ snap ] );
			else
			{
				bookmarks[ snap ] = bookmarks_t::invalid;
				//update_bookmarks();
			}
		}
		else
		{
			CString temp = save_path + _T( "snap" ) + _T( '\\' ) + filename_base + _T( '.' );
			temp.Append( snap );
			temp += _T( ".sav" );
			snap_load( temp );
		}
	}

	void snap_save( const TCHAR * path )
	{
		Gzip_File_Writer_u out;
		if ( ! out.open( path ) )
		{
			const Nes_Film & film = m_emu.film();
			const int size = m_emu.frame_rate * 60 * 5;
			const int period = m_emu.frame_rate * 60;
			const int end = film.end();
			int begin = end - size + 1;
			if ( begin < film.begin() || begin > film.end() )
				begin = film.begin();
			film.write( out, begin, end, period );
		}
	}

	void snap_save( unsigned snap )
	{
		bookmarks[ snap ] = m_emu.tell();
		//update_bookmarks();

		CString temp = save_path + _T( "snap" ) + _T( '\\' ) + filename_base + _T( '.' );
		temp.Append( snap );
		temp += _T( ".sav" );
		snap_save( temp );
	}

	LRESULT OnSnapLoad(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			CString title, filter, extension;
			title.LoadString( IDS_SNAP_LOAD_TITLE );
			filter.LoadString( IDS_SNAP_FILTER );
			extension.LoadString( IDS_SNAP_EXTENSION );
			if ( file_picker( m_hWnd, path_snap, title, filter, extension, false ) )
			{
				snap_load( path_snap );
			}
		}

		return 0;
	}

	LRESULT OnSnapSave(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			CString title, filter, extension;
			title.LoadString( IDS_SNAP_SAVE_TITLE );
			filter.LoadString( IDS_SNAP_FILTER );
			extension.LoadString( IDS_SNAP_EXTENSION );
			if ( file_picker( m_hWnd, path_snap, title, filter, extension, true ) )
			{
				snap_save( path_snap );
			}
		}

		return 0;
	}

	LRESULT OnSnapLoad_Q0(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			snap_load( ( unsigned ) 0 );
		}

		return 0;
	}

	LRESULT OnSnapLoad_Q1(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			snap_load( 1 );
		}

		return 0;
	}

	LRESULT OnSnapLoad_Q2(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			snap_load( 2 );
		}

		return 0;
	}

	LRESULT OnSnapLoad_Q3(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			snap_load( 3 );
		}

		return 0;
	}

	LRESULT OnSnapLoad_Q4(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			snap_load( 4 );
		}

		return 0;
	}

	LRESULT OnSnapLoad_Q5(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			snap_load( 5 );
		}

		return 0;
	}

	LRESULT OnSnapLoad_Q6(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			snap_load( 6 );
		}

		return 0;
	}

	LRESULT OnSnapLoad_Q7(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			snap_load( 7 );
		}

		return 0;
	}

	LRESULT OnSnapLoad_Q8(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			snap_load( 8 );
		}

		return 0;
	}

	LRESULT OnSnapLoad_Q9(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			snap_load( 9 );
		}

		return 0;
	}

	LRESULT OnSnapSave_Q0(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			snap_save( ( unsigned ) 0 );
		}

		return 0;
	}

	LRESULT OnSnapSave_Q1(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			snap_save( 1 );
		}

		return 0;
	}

	LRESULT OnSnapSave_Q2(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			snap_save( 2 );
		}

		return 0;
	}

	LRESULT OnSnapSave_Q3(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			snap_save( 3 );
		}

		return 0;
	}

	LRESULT OnSnapSave_Q4(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			snap_save( 4 );
		}

		return 0;
	}

	LRESULT OnSnapSave_Q5(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			snap_save( 5 );
		}

		return 0;
	}

	LRESULT OnSnapSave_Q6(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			snap_save( 6 );
		}

		return 0;
	}

	LRESULT OnSnapSave_Q7(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			snap_save( 7 );
		}

		return 0;
	}

	LRESULT OnSnapSave_Q8(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			snap_save( 8 );
		}

		return 0;
	}

	LRESULT OnSnapSave_Q9(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			snap_save( 9 );
		}

		return 0;
	}

	LRESULT OnMovieLoad(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			CString title, filter, extension;
			title.LoadString( IDS_FILM_LOAD_TITLE );
			filter.LoadString( IDS_FILM_FILTER );
			extension.LoadString( IDS_FILM_EXTENSION );
			if ( file_picker( m_hWnd, path_film, title, filter, extension, false ) )
			{
				Gzip_File_Reader_u in;
				const char * err = in.open( path_film );
				if ( ! err )
				{
					Nes_Film & film = m_emu.film();

					err = film.read( in );
					if ( ! err )
					{
						if ( ! core_config.record_indefinitely ) //film.make_circular( 5 * 60 * m_emu.frame_rate );
						{
							long begin = film.constrain( film.end() - 5 * 60 * m_emu.frame_rate );
							film.trim( begin, film.end() );
						}
						input_last = 0;
						m_emu.set_film( & film );
						m_TrackBar.set_range( film.begin(), film.end() );
						m_TrackBar.set_position( m_emu.tell() );
					}
					else stop_error( err );
				}
			}
		}

		return 0;
	}

	LRESULT OnMovieSave(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			CString title, filter, extension;
			title.LoadString( IDS_FILM_SAVE_TITLE );
			filter.LoadString( IDS_FILM_FILTER );
			extension.LoadString( IDS_FILM_EXTENSION );
			if ( file_picker( m_hWnd, path_film, title, filter, extension, true ) )
			{
				Gzip_File_Writer_u out;
				if ( ! out.open( path_film ) )
				{
					m_emu.film().write( out );
				}
			}
		}

		return 0;
	}

	LRESULT OnCoreReset(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			emu_speed = 1;
			emu_step = 0;
			emu_state = emu_running;
			emu_seeking = false;
			emu_was_paused = false;
			skip_input_polling = false;
			m_emu.reset();
			bookmarks.reset();
			//m_TrackBar.ClearTics( TRUE );
			UISetCheck( ID_CORE_PAUSE, 0 );
			UISetCheck( ID_CORE_REWIND, 0 );
			UISetCheck( ID_CORE_FASTFORWARD, 0 );

			input_last = 0;
			if ( m_controls ) m_controls->reset();
			if ( m_audio ) m_audio->pause( false );
		}

		return 0;
	}

	LRESULT OnCorePause(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			if ( emu_seeking )
			{
				emu_was_paused = !emu_was_paused;
				UISetCheck( ID_CORE_PAUSE, emu_was_paused );
			}
			else
			{
				emu_state = ( emu_state == emu_running ) ? emu_paused : emu_running;
				UISetCheck( ID_CORE_PAUSE, emu_state == emu_paused );
				if ( m_controls ) m_controls->set_paused( emu_state == emu_paused );
				if ( emu_state == emu_paused ) SetTimer( 0, 10 );
			}

			if ( m_audio ) m_audio->pause( emu_state == emu_paused );
		}

		return 0;
	}

	LRESULT OnCoreNextFrame(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			++emu_step;
			emu_state = emu_running;
			if ( m_controls ) m_controls->set_paused( false );
		}

		return 0;
	}

	LRESULT OnCoreRewind(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			if ( emu_speed > 0 ) emu_speed = -1;
			else emu_speed = 1;
			if ( m_controls ) m_controls->set_speed( emu_speed );
			UISetCheck( ID_CORE_REWIND, emu_speed < 0 );
		}

		return 0;
	}

	LRESULT OnCoreFastForward(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( emu_state != emu_stopped )
		{
			if ( emu_speed <= 1 ) emu_speed = 10;
			else emu_speed = 1;
			if ( m_controls ) m_controls->set_speed( emu_speed );
			UISetCheck( ID_CORE_FASTFORWARD, emu_speed > 1 );
		}

		return 0;
	}

	LRESULT OnCoreRecordIndefinitely(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		core_config.record_indefinitely = ! core_config.record_indefinitely;
		UISetCheck( ID_CORE_RECORDINDEFINITELY, core_config.record_indefinitely );

		return 0;
	}

	LRESULT OnConfigureSound(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( do_sound_config( ATL::_AtlBaseModule.GetModuleInstance(), m_hWnd, & sound_config ) )
		{
			if ( m_audio )
			{
				delete m_audio;
				m_audio = 0;
			}
		}

		return 0;
	}

	LRESULT OnConfigureInput(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if ( m_controls ) m_controls->configure( ATL::_AtlBaseModule.GetModuleInstance(), m_hWnd );

		return 0;
	}

	LRESULT OnConfigureDisplay(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		do_display_config( ATL::_AtlBaseModule.GetModuleInstance(), m_hWnd, & display_config );

		return 0;
	}

#if 0
	LRESULT OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		static BOOL bVisible = TRUE;	// initially visible
		bVisible = !bVisible;
		CReBarCtrl rebar = m_hWndToolBar;
		int nBandIndex = rebar.IdToIndex(ATL_IDW_BAND_FIRST + 1);	// toolbar is 2nd added band
		rebar.ShowBand(nBandIndex, bVisible);
		UISetCheck(ID_VIEW_TOOLBAR, bVisible);
		UpdateLayout();
		return 0;
	}
#endif

	LRESULT OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		core_config.show_status_bar = !::IsWindowVisible(m_hWndStatusBar);
		::ShowWindow(m_hWndStatusBar, core_config.show_status_bar ? SW_SHOWNOACTIVATE : SW_HIDE);
		UISetCheck(ID_VIEW_STATUS_BAR, core_config.show_status_bar );
		UpdateLayout();
		return 0;
	}

	LRESULT OnHelpControls( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CControlsDlg dlg;
		dlg.DoModal();
		return 0;
	}

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CAboutDlg dlg;
		dlg.DoModal();
		return 0;
	}
};
