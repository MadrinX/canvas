#ifndef _SURFACE_H_
#define _SURFACE_H_

#include "TextureRef.h"
#include "Color.h"
#include "FilterMode.h"
#include "Path.h"
#include "Style.h"

namespace canvas {
  class Context;

  class Surface {
  public:
    friend class Context;

    Surface(unsigned int _width, unsigned int _height)
      : texture(_width, _height),
      width(_width),
      height(_height) { }
    virtual ~Surface() { }

    virtual void resize(unsigned int _width, unsigned int _height) {
      texture.setWidth(_width);
      texture.setHeight(_height);
      width = _width;
      height = _height;
    }

    virtual void flush() { }
    virtual void markDirty() { }
    virtual unsigned char * lockMemory(bool write_access = false) = 0;
    virtual void releaseMemory() = 0;

    virtual void clip(const Path & path) = 0;
    virtual void stroke(const Path & path, const Style & style, double lineWidth) = 0;
    virtual void fill(const Path & path, const Style & style) = 0;
    
    void gaussianBlur(float hradius, float vradius);
    void colorize(const Color & color);

    const TextureRef & updateTexture();

    unsigned int getWidth() const { return width; }
    unsigned int getHeight() const { return height; }

    void setMagFilter(FilterMode mode) { mag_filter = mode; }
    void setMinFilter(FilterMode mode) { min_filter = mode; }
  
  protected:
    virtual void fillText(Context & context, const std::string & text, double x, double y) = 0;
    virtual void drawImage(Surface & _img, double x, double y, double w, double h) = 0;

    TextureRef texture;

  private:
    Surface(const Surface & other) { }
    Surface & operator=(const Surface & other) {
      return *this;
    }

    unsigned int width, height;
    FilterMode mag_filter = LINEAR;
    FilterMode min_filter = LINEAR;
  };

  class NullSurface : public Surface {

  };
};

#endif
