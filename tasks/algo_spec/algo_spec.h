#pragma once

#include "algo_impl.h"

/// Use one of the following:
/// AlgoRes ComputeIntegral(data);
/// AlgoRes ComputeUnsignedIntegral(data);
/// AlgoRes ComputeFloat(data);
/// AlgoRes ComputeGeneral(data);

template <class T>
AlgoRes Run(T data) {
    return ComputeGeneral(data);
}
