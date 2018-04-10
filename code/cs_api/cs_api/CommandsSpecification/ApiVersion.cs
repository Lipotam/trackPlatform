namespace TrackPlatform.CommandsSpecification
{
    /// <summary>
    /// Describes trackPlatform API to working
    /// </summary>
    /// <see ref="https://github.com/Lipotam/trackPlatform/wiki/Api"/>
    /// <remarks>
    /// Each API must be described in @ConnectionController handler
    /// If you add new version for API, check @ConnectionController::highestAPI field
    /// </remarks>
    public enum ApiVersion
    {
        StartBasicApi = 1,                  //default API v1
        ApiWithAnswer = 2,                  //API v2
        ApiWithAutoDiconnect = 3,           //API v3
        ApiWithCrc = 4,                     //API v4
    }
}