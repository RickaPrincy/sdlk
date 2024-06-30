#pragma once

#define DATA_DEFINITION(Class)                         \
	/* to implement */                                 \
	virtual bool operator==(const Class& other) const; \
	/* generated */                                    \
	Class() = default;                                 \
	Class(const Class& other) = default;               \
	virtual Class& operator=(const Class& other) = default;
