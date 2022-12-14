/*
 * Register on another XTX model. When a value is received for the 
 * first time, set this instance's value
 */
public void RegisterListener(IModel other)
{
    other.PropertyChanged += OtherHandler;
}

/*
 * Listener to other instance of the XTX 
 */
public void OtherHandler(object sender, PropertyChangedEventArgs e)
{
    if (e.PropertyName.Contains("IsSet"))
    {
        return;
    }

    // Get has_field for this value
    string propertyString = e.PropertyName;
    string flagPropertyString = e.PropertyName + "IsSet";

    // If not set before
    if (!(bool)GetType().GetProperty(flagPropertyString).GetValue(this, null))
    {
        // First set the value
        GetType().GetProperty(propertyString).SetValue(this, sender.GetType().GetProperty(propertyString).GetValue(sender, null));

        // Then set the flag 
        GetType().GetProperty(flagPropertyString).SetValue(this, true);

    }
}

/* 
 * Force an update event to a specific property. This is used when the value is not changed
 * according to us, but the device did not accept a previous value.
 */
public void ForceUpdate(string propertyname)
{
    OnPropertyChanged(propertyname);
}