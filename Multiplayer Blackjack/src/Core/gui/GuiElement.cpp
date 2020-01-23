#include "GuiElement.hpp"
#include <iostream>
#include "Core/Input.hpp"


namespace blackjack::core {
	GuiElement::GuiElement(const float x, const float y, const float width, const float height, const Colour colour) : Mesh(16, 6), x_(x), y_(y), width_(width), height_(height), material_(nullptr) {
		material_ = Resources::CreateMaterial("gui_" + colour, Resources::GetShader("gui"));
		material_->SetUniform4f("u_colour", (float)colour.r / 255, (float)colour.g / 255, (float)colour.b / 255, (float)colour.a/255);
		Initialise();
	}
	GuiElement::GuiElement(const float x, const float y, const float width, const float height, Material* material) : Mesh(16, 6), x_(x), y_(y), width_(width), height_(height), material_(material) {
		Initialise();
	}

	void GuiElement::Initialise() {
		vertices_[0] = x_;
		vertices_[1] = y_;
		vertices_[2] = 0;
		vertices_[3] = 1;

		vertices_[4] = x_ + width_;
		vertices_[5] = y_;
		vertices_[6] = 1;
		vertices_[7] = 1;

		vertices_[8] = x_ + width_;
		vertices_[9] = y_ + height_;
		vertices_[10] = 1;
		vertices_[11] = 0;

		vertices_[12] = x_;
		vertices_[13] = y_ + height_;
		vertices_[14] = 0;
		vertices_[15] = 0;

		indices_[0] = 0;
		indices_[1] = 1;
		indices_[2] = 2;
		indices_[3] = 2;
		indices_[4] = 3;
		indices_[5] = 0;
	}

	void GuiElement::SetX(const float x) {
		x_ = x;
		vertices_[0] = x;
		vertices_[4] = x + width_;
		vertices_[8] = x + width_;
		vertices_[12] = x;
	}
	void GuiElement::SetY(const float y) {
		y_ = y;
		if (vertex_count_ != 0) {
			vertices_[1] = y;
			vertices_[5] = y;
			vertices_[9] = y + height_;
			vertices_[13] = y + height_;
		}
	}	
	void GuiElement::SetWidth(const float width) {
		width_ = width;
		vertices_[4] = x_ + width;
		vertices_[8] = x_ + width;
	}
	void GuiElement::SetHeight(const float height) {
		height_ = height;
		vertices_[9] = y_ + height;
		vertices_[13] = y_ + height;
	}

	const float GuiElement::GetX() const {
		return x_;
	}

	const float GuiElement::GetY() const {
		return y_;
	}

	const float GuiElement::GetWidth() const {
		return width_;
	}

	const float GuiElement::GetHeight() const {
		return height_;
	}

	Material* GuiElement::GetMaterial() {
		return material_;
	}

	void GuiElement::SetMaterial(const Colour colour) {
		material_ = Resources::CreateMaterial("gui_" + colour, Resources::GetShader("gui"));
		material_->SetUniform4f("u_colour", (float)colour.r/255, (float)colour.g/255, (float)colour.b/255, (float)colour.a/255);
	}
	void GuiElement::SetMaterial(Material* material) {
		material_ = material;
	}
	void GuiElement::Update() {}

	void GuiElement::Draw(RendererUI& renderer) {
		renderer.Push(this);
	}

	bool GuiElement::MouseIntersect() {
		if (Input::GetMouseX() >= x_ && Input::GetMouseX() <= x_ + width_ && Input::GetMouseY() >= y_ && Input::GetMouseY() <= y_ + height_) {
			return true;
		}
		return false;
	}
}