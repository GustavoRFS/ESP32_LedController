import { writable } from "svelte/store";

type ConnectionStore = {
  isConnected: boolean;
  ignoringConnection: boolean;
};

export default writable<ConnectionStore>({
  ignoringConnection: false,
  isConnected: false,
});
