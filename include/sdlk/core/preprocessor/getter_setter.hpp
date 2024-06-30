#pragma once

#define CP_GETTER(type, name)              \
	virtual const type *get_##name() const \
	{                                      \
		return p_##name;                   \
	}

#define GETTER(type, name)          \
	virtual type get_##name() const \
	{                               \
		return m_##name;            \
	}

#define SETTER(type, name)             \
	virtual void set_##name(type name) \
	{                                  \
		m_##name = name;               \
	}

#define GETTER_SETTER(type, name) \
	GETTER(type, name)            \
	SETTER(type, name)
