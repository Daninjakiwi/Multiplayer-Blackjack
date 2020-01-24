#pragma once
#include "Label.hpp"

namespace blackjack::core {
	class InputBox : public Label {
	private:
		static InputBox* current_;
		static std::unique_ptr<GuiElement> cursor_;

		int max_length_;
		bool is_selected_, is_hidden_;
		unsigned char frame_count_;	
		std::string typed_text_;
		std::string hint_text_;

	public:
		InputBox(float x, float y, float width, float height, Font* font, int max_length = 0, const std::string& hint_text="", bool hidden=false);
	
		static void ProccessKey(unsigned int code);

		void SetSelected(bool selected = true);
		const bool GetSelected() const;

		void SetHidden(bool hidden);
		bool GetHidden();

		void Reset();

		const std::string& GetText() const;

		void Update();
		void Draw(RendererUI& renderer);
	};
}
