#ifndef WAVEINPUT_H
#define WAVEINPUT_H

#include <QFile>

#include "common/constructors.h"
#include "render/audioparams.h"

class WaveInput
{
public:
  WaveInput(const QString& f);

  ~WaveInput();

  DISABLE_COPY_MOVE(WaveInput)

  bool open();

  bool is_open() const;

  QByteArray read(int length);
  QByteArray read(int offset, int length);
  void read(int offset, char *buffer, int length);

  bool at_end() const;

  const AudioRenderingParams& params() const;

  void close();

  int sample_count() const;

private:
  bool find_str(QFile* f, const char* str);

  AudioRenderingParams params_;

  QFile file_;

  qint64 data_position_;

  quint32 data_size_;
};

#endif // WAVEINPUT_H
