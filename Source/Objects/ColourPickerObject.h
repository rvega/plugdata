/*
 // Copyright (c) 2023 Timothy Schoen
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "../Utility/ColourPicker.h"

class ColourPickerObject final : public TextBase {
public:
    ColourPickerObject(void* ptr, Object* object)
        : TextBase(ptr, object)
    {
    }

    void mouseDown(MouseEvent const& e) override
    {
        if (getValue<bool>(object->locked)) {
            showColourPicker();
        }
    }

    void showColourPicker()
    {
        unsigned int red, green, blue;
        auto x = static_cast<t_fake_colors*>(ptr);
        sscanf(x->x_color, "#%02x%02x%02x", &red, &green, &blue);

        ColourPicker::show(getTopLevelComponent(), true, Colour(red, green, blue), object->getScreenBounds(), [_this = SafePointer(this), x](Colour c) {
            if (!_this)
                return;

            _this->pd->lockAudioThread();

            outlet_symbol(x->x_obj.te_outlet, _this->pd->generateSymbol(String("#") + c.toString().substring(2)));
            snprintf(x->x_color, 1000, "#%02x%02x%02x", c.getRed(), c.getGreen(), c.getBlue());

            _this->pd->unlockAudioThread();
        });
    }

    std::vector<hash32> getAllMessages() override
    {
        return {
            hash("pick")
        };
    }

    void receiveObjectMessage(String const& symbol, std::vector<pd::Atom>& atoms) override
    {
        switch (hash(symbol)) {

        case hash("pick"): {
            showColourPicker();
            break;
        }
        }
    }
};
