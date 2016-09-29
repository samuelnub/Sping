#pragma once

#include <memory>

namespace Sping
{
	class Handler;

	// Should be in the style of the Handler class
	// Should contain texture, mesh, shader manager, and scene graph too
	class Renderer
	{
	public:
		Renderer(Handler &handler);
		~Renderer();

		void draw();

	protected:


	private:
		Handler &handler;

	};
}