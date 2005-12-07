#ifndef ORO_KINDYN_KINEMATICSTYPES_HPP
#define ORO_KINDYN_KINEMATICSTYPES_HPP

#include <boost/numeric/ublas/matrix.hpp>
#include <vector>

namespace ORO_KinDyn
{
    /**
     * An Orocos Jacobian is a matrix of doubles with row_major access convention.
     * Internally, it uses an unbounded array, to store rows and columns.
     * Therefore, it must be carefully used in real-time code in order not to provoke
     * internal memory allocations. Assignment and reading are safe to use at any time,
     * given that the size of the Jacobian does not change. Construction:
     @verbatim
     Jacobian v( rows, columns );
     //...
     double jx = v[r][c];
     @endverbatim
     * @see Boost::uBlas Library http://www.boost.org/libs/numeric/ublas/doc/
     */
    typedef boost::numeric::ublas::matrix<double,
                                          boost::numeric::ublas::row_major,
                                          boost::numeric::ublas::unbounded_array<double> > Jacobian;

    /**
     * The row of a Jacobian.
     * Use this for convenience to access the row of a Jacobian as in:
     @verbatim
     Jacobian v( rows, columns);
     JacobianRow myrow = (v, the_row);
     //...
     double jx = myrow[c];
     @endverbatim
     * @see Boost::uBlas Library http://www.boost.org/libs/numeric/ublas/doc/
     */
    typedef boost::numeric::ublas::matrix_row<Jacobian> JacobianRow;

    /**
     * The column of a Jacobian.
     * Use this for convenience to access the column of a Jacobian as in:
     @verbatim
     Jacobian v( rows, columns);
     JacobianColumn mycol = (v, the_column);
     //...
     double jx = mycol[r];
     @endverbatim
     * @see Boost::uBlas Library http://www.boost.org/libs/numeric/ublas/doc/
     */
    typedef boost::numeric::ublas::matrix_column<Jacobian> JacobianColumn;

    /**
     * In Orocos, the std::vector<double> is used to represent joint
     * positions, velocities, accelerations or jerk.
     */
    typedef std::vector<double> JointValues;

    /**
     * A vector of joint positions.
     */
    typedef JointValues JointPositions;

    /**
     * A vector of joint velocities.
     */
    typedef JointValues JointVelocities;

    /**
     * A vector of joint accelerations.
     */
    typedef JointValues JointAccelerations;

    /**
     * A vector of joint jerks.
     */
    typedef JointValues JointJerks;
}
#endif