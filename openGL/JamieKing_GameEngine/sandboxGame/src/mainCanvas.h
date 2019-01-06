#ifndef SANDBOXGAME_MAINCANVAS_H
#define SANDBOXGAME_MAINCANVAS_H

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/glcanvas.h>

#include <string>
using std::string;

namespace sandboxGame
{
	class MainCanvas : public wxGLCanvas
	{
	public:
		MainCanvas(wxFrame * parent, int* args);
		virtual ~MainCanvas();

		void Resized(wxSizeEvent& evt);
		void Render(wxPaintEvent& evt);
		void PaintGL();
		void MouseMoveEvent(wxMouseEvent& event);
		void KeyPressEvent(wxKeyEvent& event);

	private:
		wxGLContext * m_context;
		bool glInitialized;
		GLuint vertexBufferId;

		void SendDataToOpenGL();
		void InitializeGL();
		void InstallShaders();

		bool ShaderCompileStatus(GLuint shaderId);
		bool ProgramLinkStatus(GLuint programId);

		string ReadShaderCode(const char* fileName);
	};
}
#endif