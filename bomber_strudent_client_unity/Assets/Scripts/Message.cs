using System.Collections;
using System.Collections.Generic;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

public class Message
{
    [JsonExtensionData]
    public IDictionary<string, JToken> _additionalData;
}
