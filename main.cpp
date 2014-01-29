#include <gio/gio.h>

int main()
{
    GDBusProxy *proxy;
    GDBusProxyFlags flags;
    GError * error=NULL;
    flags = G_DBUS_PROXY_FLAGS_NONE;
    proxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SESSION,flags,
            NULL, 
            "org.mpris.MediaPlayer2.SMPlayer2",
            "/org/mpris/MediaPlayer2",
            "org.freedesktop.DBus.Properties",
            NULL,&error);

    if( proxy==NULL ) 
    {
        g_printerr("Error creating proxy:%s\n",error->message);
        g_error_free(error);
    }
    else 
    {
        error = NULL;
        g_print("creating proxy success\n");
        GVariant *ret; 
        ret  = g_dbus_proxy_call_sync(proxy,"Get",
                g_variant_new("(ss)",
                    "org.mpris.MediaPlayer2.Player","Metadata"),
               G_DBUS_CALL_FLAGS_NONE, -1,NULL,&error);
        if(ret == NULL) 
        {
            g_printerr("Error callint proxy:%s\n",error->message);
            g_error_free(error);
        }
        else
        {
            g_print("%s\n",g_variant_print(ret,TRUE) );
            g_variant_unref(ret);
        }
        g_object_unref(proxy);
    }
    return 0;
}
