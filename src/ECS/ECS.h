#ifndef ECS_H
#define ECS_H

// ------------------------------------------------------------
// All main classes for ECS
// ------------------------------------------------------------
#include "Entity.h"
#include "Component.h"
#include "System.h"

// ------------------------------------------------------------
// Supplemental classes
// ------------------------------------------------------------
#include "Signature.h"
#include "Registry.h"
#include "Object_Pool.h"

// ------------------------------------------------------------
// template implementations sorted so that the 
// circular dependencies are solved correctly
// ------------------------------------------------------------
#include "Registry_impl.h"
#include "Entity_impl.h"
#include "System_impl.h"

#endif // ECS_H