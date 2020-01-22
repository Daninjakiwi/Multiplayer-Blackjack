#pragma once
#include "Label.hpp"

namespace Blackjack::Core {
	class InputBox : public Label {
	private:
		static InputBox* current_;
		static std::unique_ptr<GuiElement> cursor_;

		int max_length_;
		bool is_selected_;
		unsigned char frame_count_;

		
	public:
		InputBox(float x, float y, float width, float height, Font* font, const Colour colour = {}, int max_length = 0, bool hidden = false);
	
		static void ProccessKey(unsigned int code);

		void Update();
		void Draw(RendererUI& renderer);
	};
}
