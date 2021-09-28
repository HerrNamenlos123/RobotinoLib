#pragma once

#include <string>
#include <exception>
#include <vector>

namespace Robotino {

	struct Color {
		float r, g, b;
	};

    class Image {

        std::vector<Color> data;

    public:
        size_t width = 0;
        size_t height = 0;
        bool valid = false;

        Image() {}

        Image(size_t width, size_t height) {
            create(width, height);
        }

        Image(const Image& img) {
            load(img);
        }

        Image(const unsigned char* data, unsigned int dataSize, unsigned int width, unsigned int height, unsigned int step) {
            load(data, dataSize, width, height, step);
        }

        void load(const Image& img) {
            create(img.width, img.height);

            for (size_t x = 0; x < width; x++) {
                for (size_t y = 0; y < height; y++) {
                    set(x, y, img.get(x, y));
                }
            }
        }

        void load(const unsigned char* data, unsigned int dataSize, unsigned int width, unsigned int height, unsigned int step) {

            if (step != width * 3) {
                throw std::exception(("Unknown image format: width " + std::to_string(width) + ", step " + std::to_string(step)).c_str());
            }

            create(width, height);
            memcpy(&this->data[0].r, data, (size_t)width * height * 3);
        }

        void create(size_t width, size_t height, const Color& fillColor = { 0, 0, 0 }) {

            if (valid)
                reset();

            this->width = width;
            this->height = height;

            data.clear();
            data.reserve(width * height * 3);
            for (size_t i = 0; i < width * height * 3; i++) {
                data.push_back(fillColor);
            }

            valid = true;
        }

		bool set(size_t x, size_t y, const Color& color) {

            if (!valid)
                return false;

            size_t index = y * width + x;
            if (index >= data.size())
                return false;

            data[index] = color;
            return true;
        }

		Color get(size_t x, size_t y) const {

            if (!valid)
                throw std::exception("Image was not initialized");

            size_t index = y * width + x;
            if (index >= data.size())
                throw std::exception("Invalid index");

            return data[index];
        }

        void flipVertical() {

            if (!valid)
                throw std::exception("Image was not initialized");

            Image img(width, height);

            for (size_t x = 0; x < width; x++) {
                for (size_t y = 0; y < height; y++) {
                    img.set(x, height - y, get(x, y));
                }
            }

            load(img);
        }

        unsigned char* raw() const {
            return (unsigned char*)&data[0];
        }

	private:
		void reset() {
            if (valid) {
                data.clear();
                valid = false;
                width = 0;
                height = 0;
            }
        }

	};

}
