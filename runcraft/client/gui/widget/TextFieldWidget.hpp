//
// Created by robcholz on 4/2/23.
//

#ifndef RUNCRAFT_TEXTFIELDWIDGET_HPP
#define RUNCRAFT_TEXTFIELDWIDGET_HPP

#include "Widget.hpp"
#include "client/GameInfo.hpp"

class TextFieldWidget : public Widget {
private:
	RichText text{gui_style::MessageFont};

	void executeCallbackFunc() override {}

	void onUpdate() override {}

protected:
	void onRender() override {
		GameInfo.getRender()->render(text);
	}

public:
	explicit TextFieldWidget(const String& id, int size, bool visible, int x, int y) :
			Widget(id, visible) {
		text.setColor(gui_style::MessageColor)
		    .setMessage(TranslatableText::getTranslatable(id, translatable::GUI_TEXTFIELD))
		    .setCharacterSize(size)
		    .setPosition((float) x, (float) y);
		setOutline(&widgetOutline, widgetSprite, x, y, (int) text.getGlobalBounds().width, (int) text.getGlobalBounds().height);
	}

	~TextFieldWidget() = default;

	bool stateChanged() = delete;

	bool activated() = delete;

	bool isPressed() = delete;

	bool isClicked() = delete;
};

#endif //RUNCRAFT_TEXTFIELDWIDGET_HPP
