#include <mbgl/style/conversion/geojson.hpp>

#include <string>
namespace mbgl {
namespace style {
namespace conversion {

template <>
optional<GeoJSON> Converter<GeoJSON>::operator()(const v8::Local<v8::Value>& value, Error& error) const {
    v8::Local<v8::Value> local = value;

    Nan::HandleScope scope;

    v8::Local<v8::Object> JSON = Nan::To<v8::Object>(
            Nan::Get(
                Nan::GetCurrentContext()->Global(),
                Nan::New("JSON").ToLocalChecked()
                ).ToLocalChecked()
            ).ToLocalChecked();

    std::string string = *Nan::Utf8String(Nan::MakeCallback(JSON, "stringify", 1, &local));
    return convert<GeoJSON>(string, error);
}

} // namespace conversion
} // namespace style
} // namespace mbgl
