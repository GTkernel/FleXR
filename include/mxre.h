#ifndef __MXRE__
#define __MXRE__

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

/* defs */
#include "defs.h"

/* AR */
#include "ar/world.h"
#include "ar/object.h"

/* ogl egl */
#include "gl/shader.h"
#include "gl/mesh.h"
#include "gl/model.h"
#include "gl/camera.h"
#include "gl/gl_utils.h"
#include "gl/gl_objects.h"
#include "gl/gl_types.h"
#include "gl/egl_utils.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


/* cv_units */
#include "cv_types.h"
#include "object_tracker.h"


/* pipeline */
/** device **/
#include "image_loader.h"
#include "device/cv_camera.h"
#include "device/cv_display.h"
#include "device/keyboard.h"

/** ctx_understanding **/
#include "object_detector.h"
#include "cuda_orb_detector.h"

/** contextualizing **/
#include "object_ctx_extractor.h"

/** rendering **/
#include "object_renderer.h"
#include "complexyolo_renderer.h"

/** network **/
#include "network/message_sender.h"
#include "network/message_receiver.h"

#include "network/static_sender.h"
#include "network/static_receiver.h"

#include "network/cvmat_receiver.h"
#include "network/cvmat_sender.h"

#include "network/rtp_frame_sender.h"
#include "network/rtp_frame_receiver.h"

/* Perceptions */
/** Complex YOLO **/
#include "perceptions/complex_yolo/prediction_receiver.h"
#include "perceptions/complex_yolo/types.h"

#endif

