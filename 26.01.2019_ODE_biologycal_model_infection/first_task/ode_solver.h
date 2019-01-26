#ifndef ODE_SOLVER_T_H
#define ODE_SOLVER_T_H

#include <memory>
#include <vector>
#include <functional>

class ode_solver_impl_t;
class ode_solver_t
{
    std::unique_ptr<ode_solver_impl_t> pImpl;
public:
    enum class method_t : int {
        adams_moulton,
        newton,
        runge_kutta,
        COUNT,
        INVALID = COUNT
    };

    enum class error_t : int
    {
        success,
        different_size_of_vec_pars,
        nullptr_rhs,
        unimplemented_method
    };

    ode_solver_t ();

    error_t solve (
            const std::vector<double> &X0,
            std::function<std::vector<double>(const std::vector<double>&, double t)> &f,
            const double t0,
            const std::vector<double> &timesteps,
            const method_t method,
            std::vector<std::vector<double>> &result ///< out
            );

    ~ode_solver_t ();
};

#endif // ODE_SOLVER_T_H
