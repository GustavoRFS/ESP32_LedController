import api from "./espApi";

export const isConnected = async () => {
  const { data } = await api.get<boolean>("/is-connected-to-wifi");

  return data;
};

export const connectToWifi = (ssid: string, password: string) =>
  api.post("/connect-to-wifi", {
    SSID: ssid,
    PWD: password,
  });
