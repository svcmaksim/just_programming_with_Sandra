#include "ode_solver.h"

class ode_solver_impl_t
{
public:
    ode_solver_t::error_t solve_by_newton (
            const std::vector<double> &X0,
            std::function<std::vector<double> (const std::vector<double> &, double)> &f,
            const double t0,
            const std::vector<double> &timesteps,
            std::vector<std::vector<double> > &result
            );
};

ode_solver_t::ode_solver_t ()
{
    pImpl.reset (new ode_solver_impl_t);
}

ode_solver_t::error_t ode_solver_t::solve (
        const std::vector<double> &X0,
        std::function<std::vector<double> (const std::vector<double> &, double)> &f,
        const double t0,
        const std::vector<double> &timesteps,
        const ode_solver_t::method_t method,
        std::vector<std::vector<double> > &result
        )
{
    switch (method) {
    case method_t::newton:
        return pImpl->solve_by_newton (X0, f, t0, timesteps, result);
    case method_t::adams_moulton:
    case method_t::runge_kutta:
    case method_t::INVALID:
        return error_t::unimplemented_method;
    }
    return error_t::success;
}

ode_solver_t::~ode_solver_t () {}

ode_solver_t::error_t ode_solver_impl_t::solve_by_newton (
        const std::vector<double> &X0,
        std::function<std::vector<double> (const std::vector<double> &, double)> &f,
        const double t0,
        const std::vector<double> &timesteps,
        std::vector<std::vector<double> > &result
        )
{
    return ode_solver_t::error_t::unimplemented_method;
}
