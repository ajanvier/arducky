#ifndef FEMTOUSB_RGBLED_h
#define FEMTOUSB_RGBLED_h

/**
 * Uses the FemtoUSB (Atmel SAM D21, E variant) with onboard
 * RGB LED (OSRAM LRTB R48G) to fade between different colours.
 *
 * See http://stackoverflow.com/questions/15803986/fading-arduino-rgb-led-from-one-color-to-the-other
 **/
class rgb_color {
    private:
        int my_r;
        int my_g;
        int my_b;
    public:
        rgb_color (int red, int green, int blue)
            :
                my_r(red),
                my_g(green),
                my_b(blue)
        {
        }
        int r() const {return my_r;}
        int b() const {return my_b;}
        int g() const {return my_g;}
};

/**
 * Fade between two colors
 */
class rgb_fader {
    private:
        int r_pin;
        int g_pin;
        int b_pin;
    public:
        /**
         * Construct the fader for the pins to manipulate.
         * make sure these are pins that support Pulse
         * width modulation (PWM), these are the digital pins
         * denoted with a tilde(~) common are ~3, ~5, ~6, ~9, ~10
         * and ~11 but check this on your type of arduino.
         */
        rgb_fader(int red_pin, int green_pin, int blue_pin)
            :
                r_pin(red_pin),
                g_pin(green_pin),
                b_pin(blue_pin)
        {
        }
        void light(const rgb_color& color);
        void fade(const rgb_color& in, const rgb_color& out, unsigned n_steps = 256, unsigned time = 10);
};

#endif
