<script lang="ts">
  import { Router, Route, navigate } from "svelte-navigator";
  import BottomTabNavigator from "../shared/components/BottomTabNavigator/index.svelte";

  import { isConnected } from "../services/connectionService";
  import { hasUpdates } from "../services/updateService";
  import ws from "../services/webSocket";
  import WifiDisconnected from "../features/WifiDisconnected/index.svelte";
  import ColorSelection from "../features/ColorSelection/index.svelte";
  import EffectsSelection from "../features/EffectsSelection/index.svelte";
  import Favorites from "../features/Favorites/index.svelte";
  import Gradient from "../features/Gradient/index.svelte";
  import { onMount } from "svelte";
  import IconButton from "@smui/icon-button";
  import Badge from "@smui-extra/badge";
  import { Icon } from "@smui/common";
  import SettingsModal from "../shared/components/SettingsModal/index.svelte";
  import UpdateModal from "../shared/components/UpdateModal/index.svelte";
  import connectionStore from "../shared/stores/connection";
  import themeStore from "../shared/stores/theme";

  let darkMode: boolean;

  let loading = false;

  let connected = false;
  let ignoreConnection = false;

  let settingsOpened = false;
  const toggleSettingsModal = () => {
    settingsOpened = !settingsOpened;
  };

  let updateAvailable = false;
  let updateOpened = false;
  const toggleUpdateModal = () => {
    updateOpened = !updateOpened;
  };

  connectionStore.subscribe(({ isConnected, ignoringConnection }) => {
    connected = isConnected;
    ignoreConnection = ignoringConnection;
  });

  themeStore.subscribe((theme) => {
    darkMode = theme === "dark";
  });

  onMount(async () => {
    loading = true;

    const isConnectedToWifi = await isConnected();

    connectionStore.update((state) => ({
      ...state,
      isConnected: isConnectedToWifi,
    }));

    loading = false;

    if (!isConnectedToWifi) return;

    if (await hasUpdates()) updateAvailable = true;
    updateAvailable = true;

    updateOpened = updateAvailable;
  });
</script>

<Router>
  <div
    style={`display:flex;flex-grow:1;justify-content:center;align-items:center;`}
  >
    <IconButton
      style="position:absolute;left:20px;top:10px"
      on:click={() =>
        themeStore.update((theme) => (theme === "dark" ? "light" : "dark"))}
    >
      <Icon class="material-icons">{darkMode ? "light_mode" : "dark_mode"}</Icon
      ></IconButton
    >
    <div style="position:absolute;right:20px;top:10px;">
      {#if updateAvailable}
        <IconButton on:click={toggleUpdateModal} color="primary"
          ><Icon class="material-icons">download</Icon><Badge
            style="min-height: 15px; min-width: 15px; padding: 0;right:8px;top:8px"
          /></IconButton
        ><UpdateModal isOpened={updateOpened} toggleModal={toggleUpdateModal} />
      {/if}
      <IconButton on:click={toggleSettingsModal} color="primary"
        ><Icon class="material-icons">settings</Icon></IconButton
      >
    </div>
    <SettingsModal
      isOpened={settingsOpened}
      toggleModal={toggleSettingsModal}
    />
    {#if !connected && !ignoreConnection}
      <Route>
        <WifiDisconnected onIgnore={() => (ignoreConnection = true)} />
      </Route>
    {:else}
      <Route path="/effects" component={EffectsSelection} />
      <Route path="/favorites" component={Favorites} />
      <Route path="/gradient" component={Gradient} />
      <Route component={ColorSelection} />

      <BottomTabNavigator />
    {/if}
  </div>
</Router>
