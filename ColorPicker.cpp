void ColorPicker::buildRgb(uint8_t* imageData, int size)
    {
        // const buildRgb = (imageData) => {
        // const rgbValues = [];
        // note that we are loopin every 4!
        // for every Red, Green, Blue and Alpha
        uint8_t* p = imageData;
        // MM_LOGI("ColorPicker buildRgb begin5 %X %X %X", *p, *(p + 1), *(p + 2));
        // std::string s = "[";
        // for (int i = 0; i < size; ++i)
        // {
        //     s += std::to_string(*(p + i)) + " ";
        // }
        // s+= "]";
        // std::ofstream mycout("/tmp/buffer.log");
        // mycout<<size<<std::endl;
        // mycout<<s<<endl;
        // mycout.close();
        // MM_LOGI("ColorPicker debug size: %d", size);


        for (int i = 0; i < size - 4; i += 4)
        {
                    // p[0] = pixel.A;
                    // p[1] = pixel.B;
                    // p[2] = pixel.G;
                    // p[3] = pixel.R;

            RGBVec vec;
            vec.r = *(p + i);
            vec.g = *(p + i + 1);
            vec.b = *(p + i + 2); // 
            // int a = *(p + i + 3);// alpha
            if (vec.r == 0 && vec.g == 0 && vec.b == 0) {
                continue;
            }
            m_rgbArrays.push_back(vec);
            // MM_LOGI("ColorPicker buildRgb while %d %d %d %d", vec.r , vec.g, vec.b, a);
            // p = p + 4;
        }
        MM_LOGE("ColorPicker buildRgb m_rgbArrays size: %d", m_rgbArrays.size());
        // for (const auto& pixel : m_rgbArrays) {
        //     MM_LOGE("ColorPicker buildRgb pixel r: %d, g: %d, b: %g", pixel.r, pixel.g, pixel.b);
        // }
    }
// returns what color channel has the biggest difference
  uint32_t ColorPicker::findBiggestColorRange(std::vector<RGBVec>& rgbArrays)
  {
    uint64_t rMin = MAX_VALUE;
    uint64_t gMin = MAX_VALUE;
    uint64_t bMin = MAX_VALUE;

    uint64_t rMax = MIN_VALUE;
    uint64_t gMax = MIN_VALUE;
    uint64_t bMax = MIN_VALUE;

    for (auto& pixel : rgbArrays) {
        rMin = std::min(rMin, pixel.r);
        gMin = std::min(gMin, pixel.g);
        bMin = std::min(bMin, pixel.b);

        rMax = std::max(rMax, pixel.r);
        gMax = std::max(gMax, pixel.g);
        bMax = std::max(bMax, pixel.b);
    }

    uint64_t rRange = rMax - rMin;
    uint64_t gRange = gMax - gMin;
    uint64_t bRange = bMax - bMin;

    // determine which color has the biggest difference
    uint64_t biggestRange = std::max(std::max(rRange, gRange), bRange);
    if (biggestRange == rRange) {
        return 0;
    } else if (biggestRange == gRange) {
        return 1;
    } else {
        return 2;
    } 
  }

/**
 * Median cut implementation
 * can be found here -> https://en.wikipedia.org/wiki/Median_cut
 */
    std::vector<RGBVec> ColorPicker::quantization(std::vector<RGBVec>& rgbArrays, int depth)
    {

        MM_LOGI("ColorPicker quantization begin: arry size: %d", rgbArrays.size());
        // Base case
        if (depth == MAX_DEPTH || rgbArrays.empty()) {
            std::vector<RGBVec> rec;
            RGBVec color;
            color.r = 0;
            color.g = 0;
            color.b = 0;
            // int count = 0;
            for (const auto& pixel : rgbArrays) {
                // count++;
                MM_LOGE("ColorPicker quantization [read pixel] r: %d, g: %d, b: %d", pixel.r, pixel.g, pixel.b);
                color.r += pixel.r;
                color.g += pixel.g;
                color.b += pixel.b;
            }
            // const color = rgbValues.reduce(
            // (prev, curr) => {
            //     prev.r += curr.r;
            //     prev.g += curr.g;
            //     prev.b += curr.b;

            //     return prev;
            // },
            // {
            //     r: 0,
            //     g: 0,
            //     b: 0,
            // }
            // );

            color.r = round(color.r / rgbArrays.size());
            color.g = round(color.g / rgbArrays.size());
            color.b = round(color.b / rgbArrays.size());
            MM_LOGI("ColorPicker quantization end1 depth: %d, color.r : %d, g: %d, b: %d, rgbArrays size: %d", depth,  color.r,  color.g,  color.b, rgbArrays.size());
            rec.push_back(color);
            return rec;
        }
        //   /**
        //    *  Recursively do the following:
        //    *  1. Find the pixel channel (red,green or blue) with biggest difference/range
        //    *  2. Order by this channel
        //    *  3. Divide in half the rgb colors list
        //    *  4. Repeat process again, until desired depth or base case
        //    */
	// 比如结果是红色，那么排序后，红色有序段长度最大
        uint32_t componentToSortBy = findBiggestColorRange(rgbArrays);
        std::sort(rgbArrays.begin() , rgbArrays.end(), [=](RGBVec &x, RGBVec &y){ 
            if (componentToSortBy == 0) {
                return x.r < y.r;
            } else if (componentToSortBy == 1) {
                return x.g < y.g;
            } else {
                return x.b < y.b;
            }
        });

        uint32_t mid = rgbArrays.size() / 2;
        MM_LOGI("ColorPicker quantization mid: %d, arry size: %d", mid, rgbArrays.size());
        std::vector<RGBVec> vec1 = std::vector<RGBVec>(rgbArrays.begin(), rgbArrays.begin() + mid);
        std::vector<RGBVec> vec2 = std::vector<RGBVec>(rgbArrays.begin() + mid + 1, rgbArrays.end());
	// 截断成两半后，各自计算的主色肯定不相同，一边是红色，一边是非红色
        std::vector<RGBVec> res1 = quantization(vec1, depth + 1);
        std::vector<RGBVec> res2 = quantization(vec2, depth + 1);
        MM_LOGI("ColorPicker quantization end2 depth: %d, mid: %d, vec1 size: %d, vec2 size: %d,  rgbArrays.size: %d, res1 size: %d, res2 size: %d", depth,  mid,  vec1.size(),  vec2.size(), rgbArrays.size(), res1.size(), res2.size());
        res1.insert(res1.end(), res2.begin(), res2.end());
        MM_LOGI("ColorPicker quantization end3 res1 size: %d", res1.size());
        return res1;
        // return [
        // ...quantization(m_rgbArrays.slice(0, mid), depth + 1),
        // ...quantization(m_rgbArrays.slice(mid + 1), depth + 1),
        // ];
    }