#pragma once

#ifdef __FLEXR_KERNEL_SAMPLE_MARKER_RENDERER__

#include <bits/stdc++.h>
#include <yaml-cpp/yaml.h>

#include "flexr_core/include/core.h"
#include "flexr_kernels/include/intermediate/sample_marker_renderer.h"

namespace flexr
{
  namespace yaml
  {

    /**
     * @brief Yaml SampleMarkerRenderer kernel
     * @see flexr::kernels::SampleMarkerRenderer
     */
    class YamlSampleMarkerRenderer: public YamlFleXRKernel
    {
      public:
        int width, height;

        YamlSampleMarkerRenderer();

        /**
         * @brief Parse SampleMarkerRenderer kernel info
         * @param node
         *  YAML node to parse
         */
        void parseSampleMarkerRenderer(const YAML::Node &node);


        /**
         * @brief Parse specifics of SampleMarkerRenderer kernel
         * @param node
         *  YAML node to parse
         */
        void parseSampleMarkerRendererSpecific(const YAML::Node &node);


        /**
         * @brief Print parsed SampleMarkerRenderer info
         */
        void printSampleMarkerRenderer();


        /**
         * @brief Print parsed SampleMarkerRenderer specifics
         */
        void printSampleMarkerRendererSpecific();


        void* make();
    };
  }
}

#endif

