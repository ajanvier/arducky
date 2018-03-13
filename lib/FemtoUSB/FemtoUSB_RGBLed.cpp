#include <Arduino.h>
#include "FemtoUSB_RGBLed.h"

void rgb_fader::light(const rgb_color& color) {
    // Put the analog pins to the proper output.
    if (color.r() > 0) {
      analogWrite(r_pin, 255 - color.r());
    }

    if (color.g() > 0) {
      analogWrite(g_pin, 255 - color.g());
    }

    if (color.b() > 0) {
      analogWrite(b_pin, 255 - color.b());
    }
}

void rgb_fader::fade(const rgb_color& in, const rgb_color& out, unsigned n_steps, unsigned time) {
    int red_diff = out.r() - in.r();
    int green_diff = out.g() - in.g();
    int blue_diff = out.b() - in.b();
    for (unsigned i = 0; i < n_steps; ++i) {
        // Output is the color that is actually written to the pins
        // and output nicely fades from in to out.
        rgb_color output (in.r() + i * red_diff / n_steps,
                          in.g() + i * green_diff / n_steps,
                          in.b() + i * blue_diff/ n_steps);

        // Put the analog pins to the proper output.
        light(output);

        delay(time);
    }
}
