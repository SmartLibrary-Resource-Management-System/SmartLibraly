#pragma once
#include <optional>
#include <string>

#include "models/Factories.h"
#include "utils/Exceptions.h"
#include "utils/HttpServer.h"
#include "utils/Json.h"

namespace Api {
HttpResponse ok(const std::string& message, Json data = Json(), int status = 200);
HttpResponse fail(const std::string& message, int status);

template <typename Action>
HttpResponse guarded(Action&& action) {
    try {
        return action();
    } catch (const LibraryException& e) {
        return fail(e.what(), e.httpStatus());
    } catch (const std::exception& e) {
        return fail(std::string("Unexpected server error: ") + e.what(), 500);
    }
}

int parseId(const std::string& text, const std::string& label); 
Json parseBody(const HttpRequest& request);                            
FieldMap toFieldMap(const Json& object);                                
int requiredInt(const Json& body, const std::string& key, const std::string& errorMessage);
std::optional<int> optionalInt(const Json& body, const std::string& key, const std::string& errorMessage);
} 
