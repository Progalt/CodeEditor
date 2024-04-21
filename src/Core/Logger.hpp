
#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream> 
#include <fmt/format.h>
#include <utility>
#include <SDL2/SDL.h>

namespace editor 
{
    enum class Severity
    {
        Fatal,      /* Fatal errors are ones the application cannot return from. If it reaches this the app will probably gracefully crash */
        Error,      /* An Error has occurred, the app will do its best to keep running as normal. */
        Warning,    /* A warning about something happening that isn't an error but could cause an error later on */
        Info,       /* Info about application execution */
    };

    /*  Converts a Severity enum to a string */
   static const std::string& SeverityToString(Severity severity) 
    {
        static const std::string fatal = "Fatal";
        static const std::string error = "Error";
        static const std::string warning = "Warning";
        static const std::string info = "Info";
        static const std::string empty = "";

            switch(severity) 
            {
            case Severity::Fatal: return fatal;
            case Severity::Error: return error;
            case Severity::Warning: return warning;
            case Severity::Info: return info;
            default: return empty; 
        }
    }

    /*
        Logger handles outputting data about how the application is performing
        Whether this be to a file or to a text output
    */
    class Logger 
    {
    public:
        
        /* Set the threshold to show messages. Anything below this threshold will be shown. */
        static void SetSeverityThreshold(Severity severity)
        {
            m_Threshold = severity; 
        }
        
        /* Base print function */
        /* TODO: Add colour functionality */
        template<class ... Args> 
        static void Print(Severity severity, const std::string& str, Args&&... args) 
        {
            // If its above the threshold it doesn't print
            if ((int)severity > (int)m_Threshold)
                return; 

            // Format the base string to use arguments 
            std::string formattedString = fmt::format(str, std::forward<Args>(args)...);
            
            // Output to stdout
            std::cout << fmt::format("[{}] -> {}\n", SeverityToString(severity), formattedString);

            if (severity == Severity::Fatal) 
            {
                // On fatal we probably want to show an error message box
                // TODO: Move SDL specific code out of here

                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal Error", formattedString.c_str(), NULL);
            }
            
        }

        // Next functions are helper functions that determine severity based on function name

        template<class ... Args> 
        static void Info(const std::string& str, Args&&... args)
        {
            Print(Severity::Info, str, std::forward<Args>(args)...);
        }

        template<class ... Args> 
        static void Warning(const std::string& str, Args&&... args)
        {
            Print(Severity::Warning, str, std::forward<Args>(args)...);
        }

        template<class ... Args> 
        static void Error(const std::string& str, Args&&... args)
        {
            Print(Severity::Error, str, std::forward<Args>(args)...);
        }

        template<class ... Args> 
        static void Fatal(const std::string& str, Args&&... args)
        {
            Print(Severity::Fatal, str, std::forward<Args>(args)...);
        }

    private:

        static Severity m_Threshold; 
    };
}

#endif // LOGGER_H 