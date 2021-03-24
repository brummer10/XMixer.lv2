
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>
#include <unistd.h>

#include <lv2.h>

///////////////////////// MACRO SUPPORT ////////////////////////////////

#define PLUGIN_URI "urn:mixer"

#ifndef max
#define max(x, y) (((x) > (y)) ? (x) : (y))
#endif
#ifndef min
#define min(x, y) (((x) < (y)) ? (x) : (y))
#endif

typedef int PortIndex;

////////////////////////////// PLUG-IN CLASS ///////////////////////////

namespace mixer {

class Xmixer
{
private:
    float* input0;
    float* input1;
    float* input2;
    float* input3;
    float* output0;
    float* gain_1;
    float gain_1_;
    float* gain_2;
    float gain_2_;
    float* gain_3;
    float gain_3_;
    float* gain_4;
    float gain_4_;
    float* vmeter_1;
    float vmeter_1_;
    float* vmeter_2;
    float vmeter_2_;
    float* vmeter_3;
    float vmeter_3_;
    float* vmeter_4;
    float vmeter_4_;

    float fConst0;
    float power0;
    float power1;
    float power2;
    float power3;
    float db_zero;

    float fg0[2];
    float fg1[2];
    float fg2[2];
    float fg3[2];

    float Rec0[2];
    int iRec0[2];
    float fRec0[2];

    float Rec1[2];
    int iRec1[2];
    float fRec1[2];

    float Rec2[2];
    int iRec2[2];
    float fRec2[2];

    float Rec3[2];
    int iRec3[2];
    float fRec3[2];

    // private functions
    inline void run_dsp_(uint32_t n_samples);
    inline void connect_(uint32_t port,void* data);
    inline void init_dsp_(uint32_t rate);
    inline void connect_all__ports(uint32_t port, void* data);
    inline void activate_f();
    inline void clean_up();
    inline void deactivate_f();
public:
    // LV2 Descriptor
    static const LV2_Descriptor descriptor;
    // static wrapper to private functions
    static void deactivate(LV2_Handle instance);
    static void cleanup(LV2_Handle instance);
    static void run(LV2_Handle instance, uint32_t n_samples);
    static void activate(LV2_Handle instance);
    static void connect_port(LV2_Handle instance, uint32_t port, void* data);
    static LV2_Handle instantiate(const LV2_Descriptor* descriptor,
                                double rate, const char* bundle_path,
                                const LV2_Feature* const* features);
    Xmixer();
    ~Xmixer();
};

// constructor
Xmixer::Xmixer() :

    gain_1(NULL),
    gain_2(NULL),
    gain_3(NULL),
    gain_4(NULL),
    vmeter_1(NULL),
    vmeter_2(NULL),
    vmeter_3(NULL),
    vmeter_4(NULL),
    input0(NULL),
    input1(NULL),
    input2(NULL),
    input3(NULL),
    output0(NULL) {};

// destructor
Xmixer::~Xmixer() { };

///////////////////////// PRIVATE CLASS  FUNCTIONS /////////////////////

void Xmixer::init_dsp_(uint32_t rate)
{
    fConst0 = (1.0 / min(192000.0, max(1.0, float(rate))));
    for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) Rec0[l1] = 0.0;
    for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) iRec0[l2] = 0;
    for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec0[l3] = 0.0;
    for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) Rec1[l1] = 0.0;
    for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) iRec1[l2] = 0;
    for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec1[l3] = 0.0;
    for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) Rec2[l1] = 0.0;
    for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) iRec2[l2] = 0;
    for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec2[l3] = 0.0;
    for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) Rec3[l1] = 0.0;
    for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) iRec3[l2] = 0;
    for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec3[l3] = 0.0;
    for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fg0[l1] = 0.0;
    for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fg1[l1] = 0.0;
    for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fg2[l1] = 0.0;
    for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fg3[l1] = 0.0;
    db_zero = 20.*log10(0.0000003); // -130db
    power0 = 20.*log10(0.0000003); // -130db
    power1 = 20.*log10(0.0000003); // -130db
}

// connect the Ports used by the plug-in class
void Xmixer::connect_(uint32_t port,void* data)
{
    switch ((PortIndex)port)
    {
        case 0:
            input0 = static_cast<float*>(data);
            break;
        case 1:
            input1 = static_cast<float*>(data);
            break;
        case 2:
            input2 = static_cast<float*>(data);
            break;
        case 3:
            input3 = static_cast<float*>(data);
            break;
        case 4:
            output0 = static_cast<float*>(data);
            break;
        case 5:
            gain_1 = static_cast<float*>(data);
            break;
        case 6:
            gain_2 = static_cast<float*>(data);
            break;
        case 7:
            gain_3 = static_cast<float*>(data);
            break;
        case 8:
            gain_4 = static_cast<float*>(data);
            break;
        case 9:
            vmeter_1 = static_cast<float*>(data);
            break;
        case 10:
            vmeter_2 = static_cast<float*>(data);
            break;
        case 11:
            vmeter_3 = static_cast<float*>(data);
            break;
        case 12:
            vmeter_4 = static_cast<float*>(data);
            break;
        default:
            break;
    }
}

void Xmixer::activate_f()
{
    // allocate the internal DSP mem
}

void Xmixer::clean_up()
{
    // delete the internal DSP mem
}

void Xmixer::deactivate_f()
{
    // delete the internal DSP mem
}

void Xmixer::run_dsp_(uint32_t n_samples)
{
    if(n_samples<1) return;

    // get controller values
#define  gain_1_ (*(gain_1))
#define  gain_2_ (*(gain_2))
#define  gain_3_ (*(gain_3))
#define  gain_4_ (*(gain_4))
#define  vmeter_1_ (*(vmeter_1))
#define  vmeter_2_ (*(vmeter_2))
#define  vmeter_3_ (*(vmeter_3))
#define  vmeter_4_ (*(vmeter_4))
    
    float fSlow0 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * gain_1_)));
    float fSlow1 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * gain_2_)));
    float fSlow2 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * gain_3_)));
    float fSlow3 = (0.0010000000000000009 * std::pow(10.0, (0.050000000000000003 * gain_4_)));
    for (uint32_t i = 0; i<n_samples; i++) {
        fg0[0] = (fSlow0 + (0.999 * fg0[1]));
        fg1[0] = (fSlow1 + (0.999 * fg1[1]));
        fg2[0] = (fSlow2 + (0.999 * fg2[1]));
        fg3[0] = (fSlow3 + (0.999 * fg3[1]));
        float tmp0 = input0[i] * fg0[0];
        float tmp1 = input1[i] * fg1[0];
        float tmp2 = input2[i] * fg2[0];
        float tmp3 = input3[i] * fg3[0];

        int iTemp0 = (iRec0[1] < 2048);
        float fTemp0 = std::fabs(tmp0);
        Rec0[0] = (iTemp0? max(Rec0[1], fTemp0):fTemp0);
        iRec0[0] = (iTemp0?(iRec0[1] + 1):1);
        fRec0[0] = (iTemp0?fRec0[1]:Rec0[1]);
        power0 = fRec0[0];

        int iTemp1 = (iRec1[1] < 2048);
        float fTemp1 = std::fabs(tmp1);
        Rec1[0] = (iTemp1? max(Rec1[1], fTemp1):fTemp1);
        iRec1[0] = (iTemp1?(iRec1[1] + 1):1);
        fRec1[0] = (iTemp1?fRec1[1]:Rec1[1]);
        power1 = fRec1[0];

        int iTemp2 = (iRec2[1] < 2048);
        float fTemp2 = std::fabs(tmp2);
        Rec2[0] = (iTemp2? max(Rec2[1], fTemp2):fTemp2);
        iRec2[0] = (iTemp2?(iRec2[1] + 1):1);
        fRec2[0] = (iTemp2?fRec2[1]:Rec2[1]);
        power2 = fRec2[0];

        int iTemp3 = (iRec3[1] < 2048);
        float fTemp3 = std::fabs(tmp3);
        Rec3[0] = (iTemp3? max(Rec3[1], fTemp3):fTemp3);
        iRec3[0] = (iTemp3?(iRec3[1] + 1):1);
        fRec3[0] = (iTemp3?fRec3[1]:Rec3[1]);
        power3 = fRec3[0];

        output0[i] = tmp0 + tmp1 + tmp2 + tmp3;

        fg0[1] = fg0[0];
        fg1[1] = fg1[0];
        fg2[1] = fg2[0];
        fg3[1] = fg3[0];
        Rec0[1] = Rec0[0];
        iRec0[1] = iRec0[0];
        fRec0[1] = fRec0[0];
        Rec1[1] = Rec1[0];
        iRec1[1] = iRec1[0];
        fRec1[1] = fRec1[0];
        Rec2[1] = Rec2[0];
        iRec2[1] = iRec2[0];
        fRec2[1] = fRec2[0];
        Rec3[1] = Rec3[0];
        iRec3[1] = iRec3[0];
        fRec3[1] = fRec3[0];

    }
    vmeter_1_ = 20.*log10(max(db_zero,power0));
    vmeter_2_ = 20.*log10(max(db_zero,power1));
    vmeter_3_ = 20.*log10(max(db_zero,power2));
    vmeter_4_ = 20.*log10(max(db_zero,power3));

#undef  gain_1_
#undef  gain_2_
#undef  gain_3_
#undef  gain_4_
#undef  vmeter_1_
#undef  vmeter_2_
#undef  vmeter_3_
#undef  vmeter_4_
}

void Xmixer::connect_all__ports(uint32_t port, void* data)
{
    // connect the Ports used by the plug-in class
    connect_(port,data); 
}

////////////////////// STATIC CLASS  FUNCTIONS  ////////////////////////

LV2_Handle 
Xmixer::instantiate(const LV2_Descriptor* descriptor,
                            double rate, const char* bundle_path,
                            const LV2_Feature* const* features)
{
    // init the plug-in class
    Xmixer *self = new Xmixer();
    if (!self) {
        return NULL;
    }
    self->init_dsp_((uint32_t)rate);
    return (LV2_Handle)self;
}

void Xmixer::connect_port(LV2_Handle instance, 
                                   uint32_t port, void* data)
{
    // connect all ports
    static_cast<Xmixer*>(instance)->connect_all__ports(port, data);
}

void Xmixer::activate(LV2_Handle instance)
{
    // allocate needed mem
    static_cast<Xmixer*>(instance)->activate_f();
}

void Xmixer::run(LV2_Handle instance, uint32_t n_samples)
{
    // run dsp
    static_cast<Xmixer*>(instance)->run_dsp_(n_samples);
}

void Xmixer::deactivate(LV2_Handle instance)
{
    // free allocated mem
    static_cast<Xmixer*>(instance)->deactivate_f();
}

void Xmixer::cleanup(LV2_Handle instance)
{
    // well, clean up after us
    Xmixer* self = static_cast<Xmixer*>(instance);
    self->clean_up();
    delete self;
}

const LV2_Descriptor Xmixer::descriptor =
{
    PLUGIN_URI ,
    Xmixer::instantiate,
    Xmixer::connect_port,
    Xmixer::activate,
    Xmixer::run,
    Xmixer::deactivate,
    Xmixer::cleanup,
    NULL
};

} // end namespace mixer

////////////////////////// LV2 SYMBOL EXPORT ///////////////////////////

extern "C"
LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
    switch (index)
    {
        case 0:
            return &mixer::Xmixer::descriptor;
        default:
            return NULL;
    }
}

///////////////////////////// FIN //////////////////////////////////////
