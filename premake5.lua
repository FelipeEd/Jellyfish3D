workspace "Jellyfish3D"
	architecture "x86_64"
	startproject "Jellyfish3D"
	configurations { "Debug", "Release" }

	-- flags
	-- {
	-- 	"MultiProcessorCompile"
	-- }

outputbindir = "bin/%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}/%{prj.name}"
outputobjdir = "bin-int/%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}/%{prj.name}"

group "Tests"
	project "glfwtest"
	location "dumb"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	systemversion "latest"

	targetdir (outputbindir)
		objdir (outputobjdir)

		files
		{
			"%{prj.location}/*.cpp",
			"%{prj.location}/*.hpp"
		}

		includedirs
		{
			"%{wks.location}/Jellyfish3D/vendor/glfw/include",
			"%{wks.location}/Jellyfish3D/vendor/glad/include"

		}

		-- defines
		-- {
		-- 	"GLFW_INCLUDE_NONE"
		-- }

		links
		{
			"glfw","glad", "X11","GL"
		}

		filter "configurations:Debug"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			runtime "Release"
			optimize "on"

group ""


group "Core"

	project "Jellyfish3D"
		location "Jellyfish3D"
		-- kind "StaticLib"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"

		targetdir (outputbindir)
		objdir (outputobjdir)

		files
		{
			"%{prj.location}/src/*.cpp",
			"%{prj.location}/src/*.hpp"
		}

		includedirs
		{
			"%{prj.location}/src",
			"%{prj.location}/vendor",
			"%{prj.location}/vendor/glad/include",
			"%{prj.location}/vendor/glfw/include"
			-- "%{prj.location}/vendor/glm",
			-- "%{prj.location}/vendor/imgui",
			-- "%{prj.location}/vendor/stbi"

		}

		defines
		{
			"GLFW_INCLUDE_NONE"
		}

		links
		{
			"glad",
			"glfw",
			"imgui",
			"stbi",
			"X11",
			"GL"
		}

		filter "configurations:Debug"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			runtime "Release"
			optimize "on"

group ""


-- group "Misc"

-- 	project "Sandbox"

-- 		location "Examples/Sandbox"
-- 		kind "ConsoleApp"
-- 		language "C++"
-- 		cppdialect "C++17"
-- 		staticruntime "off"
-- 		systemversion "latest"

-- 		targetdir (outputbindir)
-- 		objdir (outputobjdir)


-- 		files
-- 		{
-- 			"%{prj.location}/src/*.cpp",
-- 			"%{prj.location}/src/*.hpp"
-- 		}

-- 		includedirs
-- 		{
-- 			"%{wks.location}/Jellyfish3D/src",
-- 			"%{wks.location}/Jellyfish3D/vendor",
-- 			"%{wks.location}/Jellyfish3D/vendor/glfw/include",
-- 			"%{wks.location}/Jellyfish3D/vendor/glad/include"
-- 		}

-- 		links
-- 		{
-- 			"Jellyfish3D"
-- 		}
		
-- 		defines
-- 		{
-- 			"GLFW_INCLUDE_NONE"
-- 		}


-- 		filter "configurations:Debug"
-- 			runtime "Debug"
-- 			symbols "on"

-- 		filter "configurations:Release"
-- 			runtime "Release"
-- 			optimize "on"

-- group ""



group "Dependencies"
	project "glad"
		location "Jellyfish3D/vendor/glad"
		kind "StaticLib"
		language "C"
		staticruntime "on"
		systemversion "latest"

		targetdir (outputbindir)
		objdir (outputobjdir)

		files
		{
			"%{prj.location}/src/glad.c"
		}

		includedirs
		{
			"%{prj.location}/include"
		}

		filter "configurations:Debug"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			runtime "Release"
			optimize "on"


	project "glfw"
		location "Jellyfish3D/vendor/glfw"
		kind "StaticLib"
		language "C"
		staticruntime "on"
		systemversion "latest"

		targetdir (outputbindir)
		objdir (outputobjdir)

		files
		{
			"%{prj.location}/src/context.c",
			"%{prj.location}/src/egl_context.c",
			"%{prj.location}/src/egl_context.h",
			"%{prj.location}/src/init.c",
			"%{prj.location}/src/input.c",
			"%{prj.location}/src/internal.h",
			"%{prj.location}/src/monitor.c",
			"%{prj.location}/src/osmesa_context.c",
			"%{prj.location}/src/osmesa_context.h",
			"%{prj.location}/src/vulkan.c",
			"%{prj.location}/src/window.c"
		}

		filter "configurations:Debug"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			runtime "Release"
			optimize "on"

		filter "system:windows"
			files
			{
				"%{prj.location}/src/wgl_context.c",
				"%{prj.location}/src/wgl_context.h",
				"%{prj.location}/src/win32_init.c",
				"%{prj.location}/src/win32_joystick.c",
				"%{prj.location}/src/win32_joystick.h",
				"%{prj.location}/src/win32_monitor.c",
				"%{prj.location}/src/win32_platform.h",
				"%{prj.location}/src/win32_thread.c",
				"%{prj.location}/src/win32_time.c",
				"%{prj.location}/src/win32_window.c"
			}

			defines 
			{ 
				"_GLFW_WIN32",
				"_CRT_SECURE_NO_WARNINGS"
			}
		
		filter "system:linux"
			files
			{
				"%{prj.location}/src/glx_context.c",
				"%{prj.location}/src/glx_context.h",
				"%{prj.location}/src/linux_joystick.c",
				"%{prj.location}/src/linux_joystick.h",
				"%{prj.location}/src/posix_time.c",
				"%{prj.location}/src/posix_time.h",
				"%{prj.location}/src/posix_thread.c",
				"%{prj.location}/src/posix_thread.h",
				"%{prj.location}/src/x11_init.c",
				"%{prj.location}/src/x11_monitor.c",
				"%{prj.location}/src/x11_platform.h",
				"%{prj.location}/src/x11_window.c",
				"%{prj.location}/src/xkb_unicode.c",
				"%{prj.location}/src/xkb_unicode.h"
			}

			defines 
			{ 
				"_GLFW_X11"
			}
			
		filter "system:macosx"
			files
			{
				"%{prj.location}/src/cocoa_init.m",
				"%{prj.location}/src/cocoa_joystick.m",
				"%{prj.location}/src/cocoa_joystick.h",
				"%{prj.location}/src/cocoa_monitor.m",
				"%{prj.location}/src/cocoa_platform.h",
				"%{prj.location}/src/cocoa_time.c",
				"%{prj.location}/src/cocoa_window.m",
				"%{prj.location}/src/nsgl_context.m",
				"%{prj.location}/src/nsgl_context.h",
				"%{prj.location}/src/posix_thread.c",
				"%{prj.location}/src/posix_thread.h"
			}

			defines
			{ 
				"_GLFW_COCOA"
			}

	project "imgui"
		location "Jellyfish3D/vendor/imgui"
		kind "StaticLib"
		language "C++"

		targetdir (outputbindir)
		objdir (outputobjdir)

		files
		{
			"%{prj.location}/*.cpp"
		}

		includedirs
		{
			"%{wks.location}/Jellyfish3D/vendor/glfw/include",
			"%{wks.location}/Jellyfish3D/vendor/glad/include"
		}

		links
		{
			"GL","X11"
		}
		
		filter "configurations:Debug"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			runtime "Release"
			optimize "on"

	project "stbi"
		location "Jellyfish3D/vendor/stbi"
		kind "StaticLib"
		language "C++"
		staticruntime "on"
		systemversion "latest"

		targetdir (outputbindir)
		objdir (outputobjdir)

		files
		{
			"%{prj.location}/*.cpp"
		}

		includedirs
		{
			"%{prj.location}"
		}
		filter "configurations:Debug"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			runtime "Release"
			optimize "on"
			
group ""