#include "OMPropertySet.h"
#include "OMProperty.h"

#include "OMAssertions.h"

#define OMPROPERTYSET_CHUNKSIZE (20)

OMPropertySet::OMPropertySet(void)
: _count(0), _capacity(OMPROPERTYSET_CHUNKSIZE), _containingObject(0)
{
  TRACE("OMPropertySet::OMPropertySet");
  PRECONDITION("Valid Capacity", _capacity >= 0);

  _propertySet = new OMPropertySetElement[_capacity];
  for (size_t i = 0; i < _capacity; i++) {
    _propertySet[i]._valid = false;
  }
  POSTCONDITION("Valid count", ((_count >= 0) && (_count <= _capacity)));
}

OMPropertySet::~OMPropertySet(void)
{
  delete _propertySet;
  _propertySet = 0;
}

OMProperty* OMPropertySet::get(const int pid) const
{
  TRACE("OMPropertySet::get");
  OMProperty* result;
  PRECONDITION("Valid property id", pid >= 0 );
  PRECONDITION("Property set contains the property", contains(pid));
  OMPropertySetElement* element = find(pid);
  ASSERT("Element found", element != 0);
  ASSERT("Valid element", element->_valid);
  result = element->_property;
  POSTCONDITION("Valid result", result != 0);
  POSTCONDITION("Valid count", ((_count >= 0) && (_count <= _capacity)));
  return result;
}

void OMPropertySet::put(OMProperty* property)
{
  TRACE("OMPropertySet::put");
  // SAVE(_count);
  int pid = property->pid();
  PRECONDITION("Valid property id", pid >= 0);
  PRECONDITION("Property not already installed", !contains(pid));
  OMPropertySetElement* element = find();
  if (element == 0) {
    grow(OMPROPERTYSET_CHUNKSIZE);
    element = find();
  }
  ASSERT("Found space for new element", element != 0);

  element->_pid = pid;
  element->_property = property;
  element->_valid = true;
  element->_property->setContainingObject(_containingObject);
  _count++;
  POSTCONDITION("Property installed", contains(property->pid()));
  POSTCONDITION("Consistent property set",
                property == find(property->pid())->_property);
  // POSTCONDITION("Count increased by one", _count == OLD(_count) + 1);
  POSTCONDITION("Valid count", ((_count >= 0) && (_count <= _capacity)));
}

void OMPropertySet::iterate(size_t& context, OMProperty*& property) const
{
  OMPropertySetElement* element = 0;
  size_t start = context;
  size_t found = 0;

  for (size_t i = start; i < _capacity; i++) {
    if (_propertySet[i]._valid) {
      element = &_propertySet[i];
      found = i;
      break;
    }
  }
  if (element != 0) {
    property = element->_property;
    context = ++found;
  } else {
    context = 0;
  }
}

bool OMPropertySet::contains(const int pid) const
{
  OMPropertySetElement* element = find(pid);
  if (element != 0) {
    return true;
  } else {
    return false;
  }
}

size_t OMPropertySet::count(void) const
{
  POSTCONDITION("Valid count", ((_count >= 0) && (_count <= _capacity)));
  return _count;
}

void OMPropertySet::setContainingObject(const OMStorable* containingObject)
{
  _containingObject = containingObject;
  POSTCONDITION("Valid count", ((_count >= 0) && (_count <= _capacity)));
}

bool OMPropertySet::equal(const int& pida, const int& pidb)
{
  // For when PIDS are not ints
  return pida == pidb;
}

OMPropertySet::OMPropertySetElement* OMPropertySet::find(const int pid) const
{
  OMPropertySetElement* result = 0;

  for (size_t i = 0; i < _capacity; i++) {
    if (_propertySet[i]._valid) {
      if (equal(_propertySet[i]._pid, pid)) {
        result = &_propertySet[i];
        break;
      }
    }
  }
  return result;
}

OMPropertySet::OMPropertySetElement* OMPropertySet::find(void) const
{
  OMPropertySetElement* result = 0;

  for (size_t i = 0; i < _capacity; i++) {
    if (!_propertySet[i]._valid) {
      result = &_propertySet[i];
      break;
    }
  }
  return result;

}

void OMPropertySet::grow(const size_t additionalElements)
{
}
