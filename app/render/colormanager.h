#ifndef COLORSERVICE_H
#define COLORSERVICE_H

#include <memory>

#include "codec/frame.h"
#include "colorprocessor.h"

class ColorManager : public QObject
{
  Q_OBJECT
public:
  ColorManager();

  OCIO::ConstConfigRcPtr GetConfig() const;

  void SetConfig(const QString& filename);

  void SetConfig(OCIO::ConstConfigRcPtr config);

  static void DisassociateAlpha(FramePtr f);

  static void AssociateAlpha(FramePtr f);

  static void ReassociateAlpha(FramePtr f);

  QStringList ListAvailableDisplays();

  QString GetDefaultDisplay();

  QStringList ListAvailableViews(QString display);

  QString GetDefaultView(const QString& display);

  QStringList ListAvailableLooks();

  QStringList ListAvailableInputColorspaces();

  static QStringList ListAvailableInputColorspaces(OCIO::ConstConfigRcPtr config);

  enum OCIOMethod {
    kOCIOFast,
    kOCIOAccurate
  };

  static OCIOMethod GetOCIOMethodForMode(RenderMode::Mode mode);

  static void SetOCIOMethodForMode(RenderMode::Mode mode, OCIOMethod method);

signals:
  void ConfigChanged();

private:
  OCIO::ConstConfigRcPtr config_;

  enum AlphaAction {
    kAssociate,
    kDisassociate,
    kReassociate
  };

  static void AssociateAlphaPixFmtFilter(AlphaAction action, FramePtr f);

  template<typename T>
  static void AssociateAlphaInternal(AlphaAction action, T* data, int pix_count);
};

#endif // COLORSERVICE_H
