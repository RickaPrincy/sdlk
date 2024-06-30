#pragma once

#define GETTER(type, name)  \
    virtual type get_##name() const \
	{                       \
		return m_##name;    \
	}

#define SETTER(type, name)     \
	virtual void set_##name(type name) \
	{                          \
		m_##name = name;       \
	}

#define GETTER_SETTER(type, name) \
	GETTER(type, name)            \
	SETTER(type, name)
