// =============================================================================
// INLINE.
// SSE Implementation (SSE 4.1). Used for Vector instead of FPU.
// Author: Constantin Masson
// =============================================================================


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------
FORCE_INLINE VectF3::VectF3(void) {
    this->m128 = _mm_setzero_ps();
}

FORCE_INLINE VectF3::VectF3(float x, float y, float z) {
    this->m128 = _mm_setr_ps(x,y,z,0.0f);
}

FORCE_INLINE VectF3::VectF3(__m128 v) {
    this->m128 = v;
}


// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------
FORCE_INLINE float VectF3::length() const {
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(this->m128, this->m128, 0x71)));
}

FORCE_INLINE float VectF3::squareLength() const {
    return _mm_cvtss_f32(_mm_dp_ps(this->m128, this->m128, 0x71));
}

FORCE_INLINE VectF3 VectF3::normalize() const {
    __m128 l    = _mm_sqrt_ps(_mm_dp_ps(this->m128, this->m128, 0x7F));
    __m128 res  = _mm_div_ps(this->m128,l);
    res[3]      = 0.0f; // Set w to 0 (Unused)
    return VectF3(res);
}

FORCE_INLINE VectF3 VectF3::crossProduct(VectF3 const& v) const {
    __m128 rabit = _mm_sub_ps(
            _mm_mul_ps(
                _mm_shuffle_ps(this->m128, this->m128, _MM_SHUFFLE(3,0,2,1)),
                _mm_shuffle_ps(v.m128, v.m128, _MM_SHUFFLE(3,1,0,2))),
            _mm_mul_ps(
                _mm_shuffle_ps(this->m128, this->m128, _MM_SHUFFLE(3,1,0,2)),
                _mm_shuffle_ps(v.m128, v.m128, _MM_SHUFFLE(3,0,2,1))));
    rabit[3] = 0; // Set w to 0
    return VectF3(rabit);
}


// -----------------------------------------------------------------------------
// Getters - Setters
// -----------------------------------------------------------------------------
FORCE_INLINE void VectF3::set(float const x, float const y, float const z) {
    this->m128 = _mm_setr_ps(x,y,z,0.0f);
}

FORCE_INLINE void VectF3::set(VectF3 const& v) {
    this->m128 = v.m128;
}


// -----------------------------------------------------------------------------
// Static functions
// -----------------------------------------------------------------------------
FORCE_INLINE float VectF3::dotProduct(VectF3 const& v1, VectF3 const& v2) {
    return _mm_cvtss_f32(_mm_dp_ps(v1.m128, v2.m128, 0x71));
}


// -----------------------------------------------------------------------------
// Operators overload
// -----------------------------------------------------------------------------
FORCE_INLINE bool VectF3::operator==(VectF3 const& v) const {
    __m128 res = _mm_cmpeq_ps(this->m128, v.m128);
    res[3] = 0xffffffff; // This is just in case of w has been altered (For any strange raison)
    return _mm_movemask_ps(res);
}

FORCE_INLINE bool VectF3::operator!=(VectF3 const& v) const {
    __m128 res = _mm_cmpneq_ps(this->m128, v.m128);
    res[3] = 0xffffffff; // This is just in case of w has been altered (For any strange raison)
    return _mm_movemask_ps(res);
}

FORCE_INLINE VectF3 VectF3::operator*(float const s) const {
    return VectF3(this->m128 * s);
}

FORCE_INLINE VectF3 VectF3::operator/(float const s) const {
    return VectF3(this->m128 / s);
}

FORCE_INLINE VectF3 VectF3::operator+(VectF3 const& v) const {
    return VectF3(this->m128 + v.m128);
}

FORCE_INLINE VectF3 VectF3::operator-(VectF3 const& v) const {
    return VectF3(this->m128 - v.m128);
}

FORCE_INLINE VectF3& VectF3::operator*=(float const s) {
    this->m128 = this->m128 * s;
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator/=(float const s) {
    this->m128 = this->m128 / s;
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator+=(VectF3 const& v) {
    this->m128 = this->m128 + v.m128;
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator-=(VectF3 const& v) {
    this->m128 = this->m128 - v.m128;
    return *this;
}
