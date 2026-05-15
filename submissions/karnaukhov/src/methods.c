#include <math.h>
#include <stdio.h>

typedef float (*func_t)(float);

static float h(func_t f, func_t g, float x) { return f(x) - g(x); }

int root_chord(func_t f, func_t g, float a, float b, float eps, int *iters, float *x) {
    float fa = h(f, g, a), fb = h(f, g, b);
    if (fa * fb > 0) return -1;
    int k = 0;

    while (fabsf(b - a) > eps && k < 100000) 
    {
        if (fabsf(fa) < eps) { 
            b = a; 
            break; 
        }
        if (fabsf(fb) < eps) { 
            a = b; 
            break; 
        }
        float c = (a * fb - b * fa) / (fb - fa);
        float fc = h(f, g, c);
        if (fabsf(fc) < eps) { 
            a = b = c; 
            break; 
        }
        if (fa * fc <= 0) { 
            b = c; 
            fb = fc; 
        } else { 
            a = c; 
            fa = fc; 
        }
        k++;
    }
    *x = (a + b) * 0.5f;
    if (iters) *iters = k;
    return 0;
}

int root_combined(func_t f, func_t g, float a, float b, float eps, int *iters, float *x) {

    float fa = h(f, g, a), fb = h(f, g, b);
    if (fa * fb > 0) return -1;
    int k = 0;

    while (fabsf(b - a) > eps && k < 100000) 
    {
        if (fabsf(fa) < eps) { 
            b = a; 
            break; 
        }
        if (fabsf(fb) < eps) { 
            a = b; 
            break; 
        }
        float c = (a * fb - b * fa) / (fb - fa);
        float m = 0.5f * (a + b);
        float fc = h(f, g, c);
        float fm = h(f, g, m);

        if (fa * fc <= 0) { 
            b = c; 
            fb = fc; 
        } else { 
            a = c; 
            fa = fc; 
        }
        if (fa * fm <= 0) { 
            b = m; 
            fb = fm; 
        } else { 
            a = m; 
            fa = fm; 
        }
        k++;
    }
    *x = 0.5f * (a + b);
    if (iters) *iters = k;
    return 0;
}

float integral_simpson(func_t f, float a, float b, float eps) {
    int n = 2;
    float prev = 0.0f;
    while (1) {
        float h = (b - a) / n;
        float s1 = 0.0f, s2 = 0.0f;

        for (int i = 1; i < n; i += 2) s1 += f(a + i * h);
        for (int i = 2; i < n; i += 2) s2 += f(a + i * h);

        float cur = (h / 3.0f) * (f(a) + f(b) + 4.0f * s1 + 2.0f * s2);
        
        if (n > 2 && fabsf(cur - prev) < eps) return cur;

        prev = cur;
        n *= 2;
        if (n > (1 << 22)) return cur;
    }
}
