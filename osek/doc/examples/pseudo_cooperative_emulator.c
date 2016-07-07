infinite loop
{
    disable interrupts;
    if( is_active_object_ready_to_run )
    {
        find the active object with highest priority;
        enable interrupts;
        e = get the event from the active object's queue;
        dispatch the 'e' event to the active object's state machine;
    }
    else
    execute the idle processing;
}
