/***

  Olive - Non-Linear Video Editor
  Copyright (C) 2019 Olive Team

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

***/

#ifndef AUDIORENDERER_H
#define AUDIORENDERER_H

#include <QLinkedList>
#include <QOpenGLTexture>

#include "common/timerange.h"
#include "node/output/viewer/viewer.h"
#include "render/pixelformat.h"
#include "render/rendermodes.h"
#include "audiorendererdownloadthread.h"
#include "audiorendererprocessthread.h"

/**
 * @brief A multithreaded OpenGL based renderer for node systems
 */
class AudioRendererProcessor : public QObject
{
  Q_OBJECT
public:
  /**
   * @brief Renderer Constructor
   *
   * Constructing a Renderer object will not start any threads/backend on its own. Use Start() to do this and Stop()
   * when the Renderer is about to be destroyed.
   */
  AudioRendererProcessor(QObject* parent);

  virtual ~AudioRendererProcessor() override;

  void SetCacheName(const QString& s);

  /**
   * @brief Set parameters of the Renderer
   *
   * The Renderer owns the buffers that are used in the rendering process and this function sets the kind of buffers
   * to use. The Renderer must be stopped when calling this function.
   *
   * @param width
   *
   * Buffer width
   *
   * @param height
   *
   * Buffer height
   *
   * @param format
   *
   * Buffer pixel format
   */
  void SetParameters(const AudioRenderingParams &params);

  /**
   * @brief Return current instance of a RenderThread (or nullptr if there is none)
   *
   * This function attempts a dynamic_cast on QThread::currentThread() to RendererThread, which will return nullptr if
   * the cast fails (e.g. if this function is called from the main thread rather than a RendererThread).
   */
  static AudioRendererThreadBase* CurrentThread();

  static AudioParams* CurrentInstance();

  QByteArray GetCachedSamples(const rational& in, const rational& out);

  void SetViewerNode(ViewerOutput* viewer);

private:
  /**
   * @brief Allocate and start the multithreaded backend
   */
  void Start();

  /**
   * @brief Terminate and deallocate the multithreaded backend
   */
  void Stop();

  /**
   * @brief Internal function for generating the cache ID
   */
  void GenerateCacheIDInternal();

  /**
   * @brief Function called when there are frames in the queue to cache
   *
   * This function is NOT thread-safe and should only be called in the main thread.
   */
  void CacheNext();

  /**
   * @brief Return the path of the cached image at this time
   */
  QString CachePathName(const QByteArray &hash);

  /**
   * @brief Internal list of RenderProcessThreads
   */
  QVector<AudioRendererProcessThreadPtr> threads_;

  /**
   * @brief Internal variable that contains whether the Renderer has started or not
   */
  bool started_;

  AudioRenderingParams params_;

  QList<TimeRange> cache_queue_;
  QString cache_name_;
  qint64 cache_time_;
  QString cache_id_;

  bool caching_;

  bool starting_;

  ViewerOutput* viewer_node_;

  QByteArray sample_cache_;

private slots:
  void InvalidateCache(const rational &start_range, const rational &end_range);

  void ThreadCallback(const QByteArray& samples, const rational& in, const rational &out);

  void ThreadRequestSibling(NodeDependency dep);

};

#endif // AUDIORENDERER_H