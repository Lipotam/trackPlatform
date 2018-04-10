namespace TrackPlatform.CommandsSpecification
{
    /// <summary>
    /// Describes trackPlatform API to working
    /// </summary>
    /// <see ref="https://github.com/Lipotam/trackPlatform/wiki/Api"/>
    /// Each API must be described in @ConnectionController handler
    /// If you add new version for API, check @ConnectionController::highestAPI field
    public enum ApiVersion
    {
        startBasicAPI = 1, //default API v1
        APIWithAnswer = 2, //API v2
        APIWithAutoDiconnect = 3, //API v3
        APIWithCRC = 4, //API v4
    }
}