class AdapterPatternExample {
    public static void main(String[] args) {

        // Test Class Adapters
        XmlToJsonClassAdapter xmlToJsonClass = new XmlToJsonClassAdapter();
        JsonToXmlClassAdapter jsonToXmlClass = new JsonToXmlClassAdapter();

        XMLData xmlData = new XMLData("<user>John</user>");
        JSONData jsonData = new JSONData("{\"name\": \"John\"}");

        System.out.println("XML to JSON (Class): " + xmlToJsonClass.convertToJson(xmlData));
        System.out.println("JSON to XML (Class): " + jsonToXmlClass.convertToXml(jsonData));

        // Test Object Adapters
        XmlToJsonObjectAdapter xmlToJsonObject = new XmlToJsonObjectAdapter();
        JsonToXmlObjectAdapter jsonToXmlObject = new JsonToXmlObjectAdapter();

        System.out.println("XML to JSON (Object): " + xmlToJsonObject.convertToJson(xmlData));
        System.out.println("JSON to XML (Object): " + jsonToXmlObject.convertToXml(jsonData));
    }
}

// Base Processors
class XMLProcessor {
    public String processXML(String xmlData) {
        return "Processed XML: " + xmlData;
    }
}

class JSONProcessor {
    public String processJSON(String jsonData) {
        return "Processed JSON: " + jsonData;
    }
}

// Data Classes
class XMLData {
    public String data;

    public XMLData(String data) {
        this.data = data;
    }
}

class JSONData {
    public String data;

    public JSONData(String data) {
        this.data = data;
    }
}

// ---------------------------------------------------------
// CLASS ADAPTERS (using inheritance)
// ---------------------------------------------------------

// JSON → XML (Class Adapter)
class JsonToXmlClassAdapter extends JSONProcessor {
    public String convertToXml(JSONData jsonData) {
        String processedJson = processJSON(jsonData.data);
        return "<xml>" + processedJson + "</xml>";
    }
}

// XML → JSON (Class Adapter)
class XmlToJsonClassAdapter extends XMLProcessor {
    public String convertToJson(XMLData xmlData) {
        String processedXml = processXML(xmlData.data);
        return "{\"data\": \"" + processedXml + "\"}";
    }
}

// ---------------------------------------------------------
// OBJECT ADAPTERS (using composition)
// ---------------------------------------------------------

// JSON → XML (Object Adapter)
class JsonToXmlObjectAdapter {
    private JSONProcessor jsonProcessor = new JSONProcessor();

    public String convertToXml(JSONData jsonData) {
        String processedJson = jsonProcessor.processJSON(jsonData.data);
        return "<xml>" + processedJson + "</xml>";
    }
}

// XML → JSON (Object Adapter)
class XmlToJsonObjectAdapter {
    private XMLProcessor xmlProcessor = new XMLProcessor();

    public String convertToJson(XMLData xmlData) {
        String processedXml = xmlProcessor.processXML(xmlData.data);
        return "{\"data\": \"" + processedXml + "\"}";
    }
}