#include "InputBox.hpp"
#include "Core/Input.hpp"
#include "Core/Log.hpp"

namespace blackjack::core {
	InputBox* InputBox::current_ = nullptr;
	std::unique_ptr<GuiElement> InputBox::cursor_ = nullptr;

	InputBox::InputBox(float x, float y, float width, float height, Font* font, const Colour colour, int max_length, bool hidden)
		: Label(x, y, width, height, "", font, colour), max_length_(max_length), is_selected_(false), frame_count_(0) {
		if (cursor_ == nullptr) {
			Colour col(0, 0, 0);

			cursor_ = std::make_unique<GuiElement>(0, 0, 10, 40, col);
		}
		text_.SetHidden(hidden);
	}

	void InputBox::Update() {
		if (MouseIntersect()) {
			if (Input::MouseDown(InputCode::MOUSE_LEFT)) {
				if (!is_selected_) {	
					Input::SetInputCallback(ProccessKey);
					cursor_.get()->SetHeight(text_.GetFont()->GetSize());
					cursor_.get()->SetX(x_ + text_.GetOffset() + (width_/5));
					cursor_.get()->SetY(y_ + ((height_ - text_.GetFont()->GetSize()) / 2) + (text_.GetFont()->GetSize() / 5));
					current_ = this;
					is_selected_ = true;
					frame_count_ = 0;
				}
			}
		}
		else {
			if (Input::MouseDown(InputCode::MOUSE_LEFT)) {
				if (is_selected_) {
					current_ = nullptr;
					is_selected_ = false;
					frame_count_ = 0;
				}
			}
		}
		if (is_selected_) {
			frame_count_ += 1;
			frame_count_ = frame_count_ % 60;
		}
	}

	void InputBox::Draw(RendererUI& renderer) {
		if (is_selected_) {
			if (frame_count_ < 30) {
				renderer.Push(cursor_.get());
			}
		}
		Label::Draw(renderer);
	}

	void InputBox::ProccessKey(unsigned int code) {
		if (current_ != nullptr) {
			if (code == 14) {
				if (current_->text_.GetText().length() > 0) {
					current_->text_.Remove();
					cursor_.get()->SetX(current_->x_ + current_->text_.GetOffset() + (current_->width_/5));
				}
			}
			else {
				if (current_->text_.GetText().length() < current_->max_length_) {
					current_->text_.Append(code);
					cursor_.get()->SetX(current_->x_ + current_->text_.GetOffset() + (current_->width_ / 5));
				}
			}
		}
	}
}