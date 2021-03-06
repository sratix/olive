#ifndef EXPORTFORMAT_H
#define EXPORTFORMAT_H

#include <QList>
#include <QString>

class ExportFormat {
public:
  ExportFormat(const QString& name, const QString& extension, const QString& encoder, const QList<int>& vcodecs, const QList<int>& acodecs) :
    name_(name),
    extension_(extension),
    encoder_(encoder),
    video_codecs_(vcodecs),
    audio_codecs_(acodecs)
  {
  }

  const QString& name() const {return name_;}
  const QString& extension() const {return extension_;}
  const QString& encoder() const {return encoder_;}
  const QList<int>& video_codecs() const {return video_codecs_;}
  const QList<int>& audio_codecs() const {return audio_codecs_;}

private:
  QString name_;
  QString extension_;
  QString encoder_;
  QList<int> video_codecs_;
  QList<int> audio_codecs_;

};

#endif // EXPORTFORMAT_H
