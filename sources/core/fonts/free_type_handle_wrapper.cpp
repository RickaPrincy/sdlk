//
// Created by ricka on 24/08/25.
//

#include "free_type_handle_wrapper.hpp"

#include <iostream>
#include <stdexcept>

namespace sdlk
{
	free_type_handle_wrapper free_type_handle_wrapper_instance;

	free_type_handle_wrapper::free_type_handle_wrapper()
	{
		this->_ft_handle = msdfgen::initializeFreetype();
		if (!this->_ft_handle)
		{
			throw std::runtime_error("Free type handle initialization failed");
		}
	}

	 free_type_handle_wrapper::~free_type_handle_wrapper()
	{
	 	msdfgen::deinitializeFreetype(this->_ft_handle);
		std::cout << "Free type handle deinitialized" << "\n";
	}

	auto free_type_handle_wrapper::instance() -> free_type_handle_wrapper*
	{
		return &free_type_handle_wrapper_instance;
	}

	auto free_type_handle_wrapper::raw() const -> msdfgen::FreetypeHandle*
	{
		return this->_ft_handle;
	}
}