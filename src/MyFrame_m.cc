//
// Generated file, do not edit! Created by opp_msgtool 6.0 from MyFrame.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#pragma warning(disable : 4101)
#pragma warning(disable : 4065)
#endif

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wshadow"
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wc++98-compat"
#pragma clang diagnostic ignored "-Wunreachable-code-break"
#pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "MyFrame_m.h"

namespace omnetpp
{

    // Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
    // They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

    // Packing/unpacking an std::vector
    template <typename T, typename A>
    void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T, A> &v)
    {
        int n = v.size();
        doParsimPacking(buffer, n);
        for (int i = 0; i < n; i++)
            doParsimPacking(buffer, v[i]);
    }

    template <typename T, typename A>
    void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T, A> &v)
    {
        int n;
        doParsimUnpacking(buffer, n);
        v.resize(n);
        for (int i = 0; i < n; i++)
            doParsimUnpacking(buffer, v[i]);
    }

    // Packing/unpacking an std::list
    template <typename T, typename A>
    void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T, A> &l)
    {
        doParsimPacking(buffer, (int)l.size());
        for (typename std::list<T, A>::const_iterator it = l.begin(); it != l.end(); ++it)
            doParsimPacking(buffer, (T &)*it);
    }

    template <typename T, typename A>
    void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T, A> &l)
    {
        int n;
        doParsimUnpacking(buffer, n);
        for (int i = 0; i < n; i++)
        {
            l.push_back(T());
            doParsimUnpacking(buffer, l.back());
        }
    }

    // Packing/unpacking an std::set
    template <typename T, typename Tr, typename A>
    void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T, Tr, A> &s)
    {
        doParsimPacking(buffer, (int)s.size());
        for (typename std::set<T, Tr, A>::const_iterator it = s.begin(); it != s.end(); ++it)
            doParsimPacking(buffer, *it);
    }

    template <typename T, typename Tr, typename A>
    void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T, Tr, A> &s)
    {
        int n;
        doParsimUnpacking(buffer, n);
        for (int i = 0; i < n; i++)
        {
            T x;
            doParsimUnpacking(buffer, x);
            s.insert(x);
        }
    }

    // Packing/unpacking an std::map
    template <typename K, typename V, typename Tr, typename A>
    void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K, V, Tr, A> &m)
    {
        doParsimPacking(buffer, (int)m.size());
        for (typename std::map<K, V, Tr, A>::const_iterator it = m.begin(); it != m.end(); ++it)
        {
            doParsimPacking(buffer, it->first);
            doParsimPacking(buffer, it->second);
        }
    }

    template <typename K, typename V, typename Tr, typename A>
    void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K, V, Tr, A> &m)
    {
        int n;
        doParsimUnpacking(buffer, n);
        for (int i = 0; i < n; i++)
        {
            K k;
            V v;
            doParsimUnpacking(buffer, k);
            doParsimUnpacking(buffer, v);
            m[k] = v;
        }
    }

    // Default pack/unpack function for arrays
    template <typename T>
    void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
    {
        for (int i = 0; i < n; i++)
            doParsimPacking(b, t[i]);
    }

    template <typename T>
    void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
    {
        for (int i = 0; i < n; i++)
            doParsimUnpacking(b, t[i]);
    }

    // Default rule to prevent compiler from choosing base class' doParsimPacking() function
    template <typename T>
    void doParsimPacking(omnetpp::cCommBuffer *, const T &t)
    {
        throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
    }

    template <typename T>
    void doParsimUnpacking(omnetpp::cCommBuffer *, T &t)
    {
        throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
    }

} // namespace omnetpp

class bitsDescriptor : public omnetpp::cClassDescriptor
{
private:
    mutable const char **propertyNames;
    enum FieldConstants
    {
    };

public:
    bitsDescriptor();
    virtual ~bitsDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue &value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(bitsDescriptor)

    bitsDescriptor::bitsDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(bits)), "")
{
    propertyNames = nullptr;
}

bitsDescriptor::~bitsDescriptor()
{
    delete[] propertyNames;
}

bool bitsDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<bits *>(obj) != nullptr;
}

const char **bitsDescriptor::getPropertyNames() const
{
    if (!propertyNames)
    {
        static const char *names[] = {"existingClass", nullptr};
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *bitsDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass"))
        return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int bitsDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0 + base->getFieldCount() : 0;
}

unsigned int bitsDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *bitsDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int bitsDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *bitsDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **bitsDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field)
    {
    default:
        return nullptr;
    }
}

const char *bitsDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field)
    {
    default:
        return nullptr;
    }
}

int bitsDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    bits *pp = omnetpp::fromAnyPtr<bits>(object);
    (void)pp;
    switch (field)
    {
    default:
        return 0;
    }
}

void bitsDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
        {
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    bits *pp = omnetpp::fromAnyPtr<bits>(object);
    (void)pp;
    switch (field)
    {
    default:
        throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'bits'", field);
    }
}

const char *bitsDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object, field, i);
        field -= base->getFieldCount();
    }
    bits *pp = omnetpp::fromAnyPtr<bits>(object);
    (void)pp;
    switch (field)
    {
    default:
        return nullptr;
    }
}

std::string bitsDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object, field, i);
        field -= base->getFieldCount();
    }
    bits *pp = omnetpp::fromAnyPtr<bits>(object);
    (void)pp;
    switch (field)
    {
    default:
        return "";
    }
}

void bitsDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
        {
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    bits *pp = omnetpp::fromAnyPtr<bits>(object);
    (void)pp;
    switch (field)
    {
    default:
        throw omnetpp::cRuntimeError("Cannot set field %d of class 'bits'", field);
    }
}

omnetpp::cValue bitsDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldValue(object, field, i);
        field -= base->getFieldCount();
    }
    bits *pp = omnetpp::fromAnyPtr<bits>(object);
    (void)pp;
    switch (field)
    {
    default:
        throw omnetpp::cRuntimeError("Cannot return field %d of class 'bits' as cValue -- field index out of range?", field);
    }
}

void bitsDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue &value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
        {
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    bits *pp = omnetpp::fromAnyPtr<bits>(object);
    (void)pp;
    switch (field)
    {
    default:
        throw omnetpp::cRuntimeError("Cannot set field %d of class 'bits'", field);
    }
}

const char *bitsDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr bitsDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    bits *pp = omnetpp::fromAnyPtr<bits>(object);
    (void)pp;
    switch (field)
    {
    default:
        return omnetpp::any_ptr(nullptr);
    }
}

void bitsDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
        {
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    bits *pp = omnetpp::fromAnyPtr<bits>(object);
    (void)pp;
    switch (field)
    {
    default:
        throw omnetpp::cRuntimeError("Cannot set field %d of class 'bits'", field);
    }
}

MyFrame_Base::MyFrame_Base(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

MyFrame_Base::MyFrame_Base(const MyFrame_Base &other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

MyFrame_Base::~MyFrame_Base()
{
}

MyFrame_Base &MyFrame_Base::operator=(const MyFrame_Base &other)
{
    if (this == &other)
        return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void MyFrame_Base::copy(const MyFrame_Base &other)
{
    this->seqNum = other.seqNum;
    this->payload = other.payload;
    this->frameType = other.frameType;
    this->ackNackNumber = other.ackNackNumber;
    this->parity = other.parity;
}

void MyFrame_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b, this->seqNum);
    doParsimPacking(b, this->payload);
    doParsimPacking(b, this->frameType);
    doParsimPacking(b, this->ackNackNumber);
    doParsimPacking(b, this->parity);
}

void MyFrame_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b, this->seqNum);
    doParsimUnpacking(b, this->payload);
    doParsimUnpacking(b, this->frameType);
    doParsimUnpacking(b, this->ackNackNumber);
    doParsimUnpacking(b, this->parity);
}

int MyFrame_Base::getSeqNum() const
{
    return this->seqNum;
}

void MyFrame_Base::setSeqNum(int seqNum)
{
    this->seqNum = seqNum;
}

const char *MyFrame_Base::getPayload() const
{
    return this->payload.c_str();
}

void MyFrame_Base::setPayload(const char *payload)
{
    this->payload = payload;
}

int MyFrame_Base::getFrameType() const
{
    return this->frameType;
}

void MyFrame_Base::setFrameType(int frameType)
{
    this->frameType = frameType;
}

int MyFrame_Base::getAckNackNumber() const
{
    return this->ackNackNumber;
}

void MyFrame_Base::setAckNackNumber(int ackNackNumber)
{
    this->ackNackNumber = ackNackNumber;
}

const bits &MyFrame_Base::getParity() const
{
    return this->parity;
}

void MyFrame_Base::setParity(const bits &parity)
{
    this->parity = parity;
}

class MyFrameDescriptor : public omnetpp::cClassDescriptor
{
private:
    mutable const char **propertyNames;
    enum FieldConstants
    {
        FIELD_seqNum,
        FIELD_payload,
        FIELD_frameType,
        FIELD_ackNackNumber,
        FIELD_parity,
    };

public:
    MyFrameDescriptor();
    virtual ~MyFrameDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue &value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(MyFrameDescriptor)

    MyFrameDescriptor::MyFrameDescriptor() : omnetpp::cClassDescriptor("MyFrame", "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

MyFrameDescriptor::~MyFrameDescriptor()
{
    delete[] propertyNames;
}

bool MyFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<MyFrame_Base *>(obj) != nullptr;
}

const char **MyFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames)
    {
        static const char *names[] = {"customize", nullptr};
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *MyFrameDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "customize"))
        return "true";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int MyFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5 + base->getFieldCount() : 5;
}

unsigned int MyFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE, // FIELD_seqNum
        FD_ISEDITABLE, // FIELD_payload
        FD_ISEDITABLE, // FIELD_frameType
        FD_ISEDITABLE, // FIELD_ackNackNumber
        FD_ISCOMPOUND, // FIELD_parity
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *MyFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "seqNum",
        "payload",
        "frameType",
        "ackNackNumber",
        "parity",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int MyFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "seqNum") == 0)
        return baseIndex + 0;
    if (strcmp(fieldName, "payload") == 0)
        return baseIndex + 1;
    if (strcmp(fieldName, "frameType") == 0)
        return baseIndex + 2;
    if (strcmp(fieldName, "ackNackNumber") == 0)
        return baseIndex + 3;
    if (strcmp(fieldName, "parity") == 0)
        return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *MyFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_seqNum
        "string", // FIELD_payload
        "int",    // FIELD_frameType
        "int",    // FIELD_ackNackNumber
        "bits",   // FIELD_parity
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **MyFrameDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field)
    {
    default:
        return nullptr;
    }
}

const char *MyFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field)
    {
    default:
        return nullptr;
    }
}

int MyFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    MyFrame_Base *pp = omnetpp::fromAnyPtr<MyFrame_Base>(object);
    (void)pp;
    switch (field)
    {
    default:
        return 0;
    }
}

void MyFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
        {
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    MyFrame_Base *pp = omnetpp::fromAnyPtr<MyFrame_Base>(object);
    (void)pp;
    switch (field)
    {
    default:
        throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'MyFrame_Base'", field);
    }
}

const char *MyFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object, field, i);
        field -= base->getFieldCount();
    }
    MyFrame_Base *pp = omnetpp::fromAnyPtr<MyFrame_Base>(object);
    (void)pp;
    switch (field)
    {
    default:
        return nullptr;
    }
}

std::string MyFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object, field, i);
        field -= base->getFieldCount();
    }
    MyFrame_Base *pp = omnetpp::fromAnyPtr<MyFrame_Base>(object);
    (void)pp;
    switch (field)
    {
    case FIELD_seqNum:
        return long2string(pp->getSeqNum());
    case FIELD_payload:
        return oppstring2string(pp->getPayload());
    case FIELD_frameType:
        return long2string(pp->getFrameType());
    case FIELD_ackNackNumber:
        return long2string(pp->getAckNackNumber());
    case FIELD_parity:
        return "";
    default:
        return "";
    }
}

void MyFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
        {
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    MyFrame_Base *pp = omnetpp::fromAnyPtr<MyFrame_Base>(object);
    (void)pp;
    switch (field)
    {
    case FIELD_seqNum:
        pp->setSeqNum(string2long(value));
        break;
    case FIELD_payload:
        pp->setPayload((value));
        break;
    case FIELD_frameType:
        pp->setFrameType(string2long(value));
        break;
    case FIELD_ackNackNumber:
        pp->setAckNackNumber(string2long(value));
        break;
    default:
        throw omnetpp::cRuntimeError("Cannot set field %d of class 'MyFrame_Base'", field);
    }
}

omnetpp::cValue MyFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldValue(object, field, i);
        field -= base->getFieldCount();
    }
    MyFrame_Base *pp = omnetpp::fromAnyPtr<MyFrame_Base>(object);
    (void)pp;
    switch (field)
    {
    case FIELD_seqNum:
        return pp->getSeqNum();
    case FIELD_payload:
        return pp->getPayload();
    case FIELD_frameType:
        return pp->getFrameType();
    case FIELD_ackNackNumber:
        return pp->getAckNackNumber();
    case FIELD_parity:
        return omnetpp::toAnyPtr(&pp->getParity());
        break;
    default:
        throw omnetpp::cRuntimeError("Cannot return field %d of class 'MyFrame_Base' as cValue -- field index out of range?", field);
    }
}

void MyFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue &value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
        {
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    MyFrame_Base *pp = omnetpp::fromAnyPtr<MyFrame_Base>(object);
    (void)pp;
    switch (field)
    {
    case FIELD_seqNum:
        pp->setSeqNum(omnetpp::checked_int_cast<int>(value.intValue()));
        break;
    case FIELD_payload:
        pp->setPayload(value.stringValue());
        break;
    case FIELD_frameType:
        pp->setFrameType(omnetpp::checked_int_cast<int>(value.intValue()));
        break;
    case FIELD_ackNackNumber:
        pp->setAckNackNumber(omnetpp::checked_int_cast<int>(value.intValue()));
        break;
    default:
        throw omnetpp::cRuntimeError("Cannot set field %d of class 'MyFrame_Base'", field);
    }
}

const char *MyFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field)
    {
    case FIELD_parity:
        return omnetpp::opp_typename(typeid(bits));
    default:
        return nullptr;
    };
}

omnetpp::any_ptr MyFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    MyFrame_Base *pp = omnetpp::fromAnyPtr<MyFrame_Base>(object);
    (void)pp;
    switch (field)
    {
    case FIELD_parity:
        return omnetpp::toAnyPtr(&pp->getParity());
        break;
    default:
        return omnetpp::any_ptr(nullptr);
    }
}

void MyFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base)
    {
        if (field < base->getFieldCount())
        {
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    MyFrame_Base *pp = omnetpp::fromAnyPtr<MyFrame_Base>(object);
    (void)pp;
    switch (field)
    {
    default:
        throw omnetpp::cRuntimeError("Cannot set field %d of class 'MyFrame_Base'", field);
    }
}

namespace omnetpp
{

} // namespace omnetpp
