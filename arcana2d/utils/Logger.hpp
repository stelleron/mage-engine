#ifndef ARCANA2D_LOGGER
    #define ARCANA2D_LOGGER
    // Includes
    #include <functional>
    #include <string>
    #include "geom/Vertex.hpp"

    namespace arcana {
        // Enumerate the types of messages 
        enum MessageType {
            Message,
            Error,
        };

        // Used to signify the end of a logged message
        struct EndLog{
            MessageType mType;
            EndLog() {
                mType = Message;
            }
            EndLog(MessageType mType) {
                this->mType = mType;
            }
        };

        // Used to create an internal logger
        class Logger {
            private:
                std::function<void(const char*)> logCallback;
                std::function<void(const char*)> errorCallback;
                std::string message;
            public:
                // Constructor
                Logger();

                // Callback setter
                void disable(); // Disable the loggers
                void useDefault(); // Use default loggers
                void setLogCallback(std::function<void(const char*)> callback); // Set a logger callback
                void setErrorCallback(std::function<void(const char*)> callback); // Set an error callback

                // Logging
                Logger& operator<<(const std::string& message);
                Logger& operator<<(const char character);
                Logger& operator<<(const char* message);
                Logger& operator<<(const int num);
                Logger& operator<<(const unsigned int num);
                Logger& operator<<(const float num);
                Logger& operator<<(const unsigned long num);
                Logger& operator<<(const Vertex vertex);
                void operator<<(const EndLog end);
        };

        // Exposes the logger
        extern Logger logger;
        extern EndLog endMessage;
        extern EndLog endError;

        // Simple log macro
        #define LOG(arg) arcana::logger << arg << arcana::endMessage;
        #define ERROR(arg) arcana::logger << arg << arcana::endError;
    }
#endif