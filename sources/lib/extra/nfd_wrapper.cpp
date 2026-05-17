//
// Created by ricka on 2026-02-07.
//

#include <nfd.h>

#include <iostream>
#include <sdlk/extra/nfd_wrapper.hpp>

namespace sdlk
{
	const auto INSTANCE = std::make_shared<nfd_wrapper>();

	nfd_wrapper::nfd_wrapper()
	{
		NFD_Init();
	}

	nfd_wrapper::~nfd_wrapper()
	{
		NFD_Quit();
	}

	auto nfd_wrapper::instance() -> std::shared_ptr<nfd_wrapper>
	{
		return INSTANCE;
	}

	auto nfd_wrapper::open_file_dialog(const std::vector<nfd_filter>& filters)
		-> nfd_open_dialog_result
	{
		std::vector<nfdu8filteritem_t> filters_value{};
		filters_value.reserve(filters.size());

		for (const auto& [m_name, m_extensions] : filters)
		{
			filters_value.emplace_back(
				nfdu8filteritem_t{ .name = m_name.c_str(), .spec = m_extensions.c_str() });
		}

		nfdu8char_t* output_path = nullptr;
		nfdopendialogu8args_t args{};

		args.filterList = filters_value.data();
		args.filterCount = filters_value.size();

		switch (const nfdresult_t _result = NFD_OpenDialogU8_With(&output_path, &args))
		{
			case NFD_OKAY:
			{
				std::string path_str(output_path);
				NFD_FreePathU8(output_path);
				return nfd_open_dialog_result(nfd_open_dialog_result::type::success, path_str);
			}
			case NFD_CANCEL: return nfd_open_dialog_result(nfd_open_dialog_result::type::canceled);
			case NFD_ERROR:
			default:
				std::cerr << "NFD error: " << NFD_GetError() << std::endl;
				return nfd_open_dialog_result(nfd_open_dialog_result::type::error);
		}
	}

    auto nfd_wrapper::open_folder_dialog() -> nfd_open_dialog_result
	{
	    nfdu8char_t* out_path = nullptr;
        constexpr nfdpickfolderu8args_t args{};

	    switch (const nfdresult_t result = NFD_PickFolderU8_With(&out_path, &args))
	    {
	        case NFD_OKAY:
	        {
	            std::string path(out_path);
	            NFD_FreePathU8(out_path);

	            return nfd_open_dialog_result(
                    nfd_open_dialog_result::type::success,
                    path
                );
	        }

	        case NFD_CANCEL:
	            return nfd_open_dialog_result(
                    nfd_open_dialog_result::type::canceled
                );

	        case NFD_ERROR:
	        default:
	            std::cerr << "NFD error: " << NFD_GetError() << std::endl;
	            return nfd_open_dialog_result(
                    nfd_open_dialog_result::type::error
                );
	    }
	}
}  // namespace sdlk
