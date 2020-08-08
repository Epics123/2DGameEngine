#include <Mayhem.h>
#include <Mayhem/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Mayhem
{
	class MayhemEditor : public Mayhem::Application

	{
	public:
		MayhemEditor()
			: Application("Mayhem Editor")
		{
			pushLayer(new EditorLayer());
		}

		~MayhemEditor()
		{

		}
	};

	Application* createApplication()
	{
		return new MayhemEditor();
	}
}
