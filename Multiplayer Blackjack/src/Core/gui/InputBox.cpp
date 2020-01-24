#include "Core/Log.hpp"
#include "InputBox.hpp"
#include "Core/Input.hpp"

namespace blackjack::core {
	InputBox* InputBox::current_ = nullptr;
	std::unique_ptr<GuiElement> InputBox::cursor_ = nullptr;

	InputBox::InputBox(float x, float y, float width, float height, Font* font, int max_length, const std::string& hint_text, bool hidden)
		: Label(x, y, width, height, hint_text, font), max_length_(max_length), is_selected_(false), frame_count_(0), typed_text_(""), hint_text_(hint_text),is_hidden_(hidden) {
		if (cursor_ == nullptr) {
			Colour col(0, 0, 0);

			cursor_ = std::make_unique<GuiElement>(0.0f, 0.0f, 10.0f, 40.0f, col);
		}
	}

	void InputBox::Reset() {
		typed_text_ = "";
		text_.SetText(typed_text_);
		SetSelected(false);
	}

	const std::string& InputBox::GetText() const {
		return typed_text_;
	}

	bool InputBox::GetHidden() {
		return is_hidden_;
	}

	void InputBox::SetHidden(bool hidden) {
		if (hidden != is_hidden_) {
			is_hidden_ = hidden;
			if (hidden) {
				if (typed_text_.length() > 0) {
					std::string new_text = "";
					for (int i = 0; i < typed_text_.length(); i++) {
						new_text += '*';
					}
					text_.SetText(new_text);
				}
			}
			else {
				text_.SetText(typed_text_);
			}
		}

	}

	void InputBox::SetSelected(bool selected) {
		if (selected) {
			if (!is_selected_) {
				if (typed_text_.length() == 0) {
					text_.SetText(typed_text_);
				}		
				Input::SetInputCallback(ProccessKey);
				cursor_.get()->SetHeight((float)text_.GetFont()->GetSize());
				cursor_.get()->SetX(x_ + text_.GetOffset() + padx_);
				cursor_.get()->SetY(y_ + ((height_ - text_.GetFont()->GetSize()) / 2));// + (text_.GetFont()->GetSize() / 5));
				current_ = this;
				is_selected_ = true;
				frame_count_ = 0;
			}
		}
		else {
			if (typed_text_.length() == 0) {
				text_.SetText(hint_text_);
			}
			is_selected_ = false;
			frame_count_ = 0;
		}
	}

	const bool InputBox::GetSelected() const {
		return is_selected_;
	}

	void InputBox::Update() {
		if (draw_) {
			if (MouseIntersect()) {
				if (Input::MouseDown(InputCode::MOUSE_LEFT)) {
					SetSelected(true);
				}
			}
			else {
				if (Input::MouseDown(InputCode::MOUSE_LEFT)) {
					SetSelected(false);
				}
			}
			if (is_selected_) {
				frame_count_ += 1;
				frame_count_ = frame_count_ % 60;
			}
		}

	}

	void InputBox::Draw(RendererUI& renderer) {
		if (draw_) {
			if (is_selected_) {
				if (frame_count_ < 30) {
					renderer.Push(cursor_.get());
				}
			}
			Label::Draw(renderer);
		}
	}

	void InputBox::ProccessKey(unsigned int code) {
		if (current_ != nullptr) {
			if (code == 14) {
				if (current_->text_.GetText().length() > 0) {
					current_->typed_text_ = current_->typed_text_.substr(0, current_->typed_text_.length()-1);
					current_->text_.Remove();
					cursor_.get()->SetX(current_->x_ + current_->text_.GetOffset() + current_->padx_);
				}
			}
			else {
				if (current_->text_.GetText().length() < current_->max_length_) {
					current_->typed_text_ += code;
					if (current_->is_hidden_) {
						current_->text_.Append('*');
					}
					else {
						current_->text_.Append(code);
					}
					
					cursor_.get()->SetX(current_->x_ + current_->text_.GetOffset() + current_->padx_);
				}
			}
		}
	}
}