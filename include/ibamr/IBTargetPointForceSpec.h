// Filename: IBTargetPointForceSpec.h
// Created on 21 Mar 2007 by Boyce Griffith
//
// Copyright (c) 2002-2017, Boyce Griffith
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of The University of North Carolina nor the names of
//      its contributors may be used to endorse or promote products derived from
//      this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef included_IBAMR_IBTargetPointForceSpec
#define included_IBAMR_IBTargetPointForceSpec

/////////////////////////////// INCLUDES /////////////////////////////////////


#include "ibtk/Streamable.h"
#include "ibtk/StreamableFactory.h"
#include "ibtk/ibtk_utilities.h"
#include "tbox/Pointer.h"

namespace SAMRAI
{
namespace hier
{
template <int DIM>
class IntVector;
} // namespace hier
namespace tbox
{
class AbstractStream;
} // namespace tbox
} // namespace SAMRAI

/////////////////////////////// CLASS DEFINITION /////////////////////////////

namespace IBAMR
{
/*!
 * \brief Class IBTargetPointForceSpec encapsulates the data necessary to
 * compute the penalty force generated by a single fixed target point (i.e., a
 * force that approximately imposes a Dirichlet boundary condition at a single
 * node of the Lagrangian mesh).
 */
class IBTargetPointForceSpec : public IBTK::Streamable
{
public:
    /*!
     * \brief Register this class and its factory class with the singleton
     * IBTK::StreamableManager object.  This method must be called before any
     * IBTargetPointForceSpec objects are created.
     *
     * \note This method is collective on all MPI processes.  This is done to
     * ensure that all processes employ the same class ID for the
     * IBTargetPointForceSpec class.
     */
    static void registerWithStreamableManager();

    /*!
     * \brief Returns a boolean indicating whether the class has been registered
     * with the singleton IBTK::StreamableManager object.
     */
    static bool getIsRegisteredWithStreamableManager();

    /*!
     * The unique class ID for this object type assigned by the
     * IBTK::StreamableManager.
     */
    static int STREAMABLE_CLASS_ID;

    /*!
     * \brief Default constructor.
     */
    IBTargetPointForceSpec(int master_idx = -1,
                           double kappa_target = 0.0,
                           double eta_target = 0.0,
                           const IBTK::Point& X_target = IBTK::Point::Zero());

    /*!
     * \return A const reference to the master node index.
     */
    const int& getMasterNodeIndex() const;

    /*!
     * \return A non-const reference to the master node index.
     */
    int& getMasterNodeIndex();

    /*!
     * \return A const reference to the stiffness of the spring attached to the
     * target point.
     */
    const double& getStiffness() const;

    /*!
     * \return A non-const reference to the stiffness of the spring attached to
     * the target point.
     */
    double& getStiffness();

    /*!
     * \return A const reference to the damping factor of the spring attached to
     * the target point.
     */
    const double& getDamping() const;

    /*!
     * \return A non-const reference to the damping factor of the spring
     * attached to the target point.
     */
    double& getDamping();

    /*!
     * \return A const reference to the position of the target point attached to
     * the node.
     */
    const IBTK::Point& getTargetPointPosition() const;

    /*!
     * \return A non-const reference to the position of the target point
     * attached to the node.
     */
    IBTK::Point& getTargetPointPosition();

    /*!
     * \brief Return the unique identifier used to specify the
     * IBTK::StreamableFactory object used by the IBTK::StreamableManager to
     * extract Streamable objects from data streams.
     */
    int getStreamableClassID() const override;

    /*!
     * \brief Return an upper bound on the amount of space required to pack the
     * object to a buffer.
     */
    size_t getDataStreamSize() const override;

    /*!
     * \brief Pack data into the output stream.
     */
    void packStream(SAMRAI::tbox::AbstractStream& stream) override;

private:
    /*!
     * \brief Copy constructor.
     *
     * \note This constructor is not implemented and should not be used.
     *
     * \param from The value to copy to this object.
     */
    IBTargetPointForceSpec(const IBTargetPointForceSpec& from) = delete;

    /*!
     * \brief Assignment operator.
     *
     * \note This operator is not implemented and should not be used.
     *
     * \param that The value to assign to this object.
     *
     * \return A reference to this object.
     */
    IBTargetPointForceSpec& operator=(const IBTargetPointForceSpec& that) = delete;

    /*!
     * Data required to define the target point penalty forces.
     */
    int d_master_idx;
    double d_kappa_target, d_eta_target;
    IBTK::Point d_X_target;

    /*!
     * \brief A factory class to rebuild IBTargetPointForceSpec objects from
     * SAMRAI::tbox::AbstractStream data streams.
     */
    class Factory : public IBTK::StreamableFactory
    {
    public:
        /*!
         * \brief Destructor.
         */
        ~Factory() = default;

        /*!
         * \brief Return the unique identifier used to specify the
         * IBTK::StreamableFactory object used by the IBTK::StreamableManager to
         * extract IBTargetPointForceSpec objects from data streams.
         */
        int getStreamableClassID() const override;

        /*!
         * \brief Set the unique identifier used to specify the
         * IBTK::StreamableFactory object used by the IBTK::StreamableManager to
         * extract IBTargetPointForceSpec objects from data streams.
         */
        void setStreamableClassID(int class_id) override;

        /*!
         * \brief Build an IBTargetPointForceSpec object by unpacking data from the
         * data stream.
         */
        SAMRAI::tbox::Pointer<IBTK::Streamable> unpackStream(SAMRAI::tbox::AbstractStream& stream,
                                                             const SAMRAI::hier::IntVector<NDIM>& offset) override;

    private:
        /*!
         * \brief Default constructor.
         */
        Factory();

        /*!
         * \brief Copy constructor.
         *
         * \note This constructor is not implemented and should not be used.
         *
         * \param from The value to copy to this object.
         */
        Factory(const Factory& from) = delete;

        /*!
         * \brief Assignment operator.
         *
         * \note This operator is not implemented and should not be used.
         *
         * \param that The value to assign to this object.
         *
         * \return A reference to this object.
         */
        Factory& operator=(const Factory& that) = delete;

        friend class IBTargetPointForceSpec;
    };
    using IBTargetPointForceSpecFactory = IBTargetPointForceSpec::Factory;
};
} // namespace IBAMR

/////////////////////////////// INLINE ///////////////////////////////////////

#include "ibamr/private/IBTargetPointForceSpec-inl.h" // IWYU pragma: keep

//////////////////////////////////////////////////////////////////////////////

#endif //#ifndef included_IBAMR_IBTargetPointForceSpec
