<script lang="ts">
  import { Router, Route, navigate } from "svelte-navigator";
  import BottomTabNavigator from "../shared/components/BottomTabNavigator/index.svelte";

  import WifiDisconnected from "../features/WifiDisconnected/index.svelte";
  import ColorSelection from "../features/ColorSelection/index.svelte";
  import EffectsSelection from "../features/EffectsSelection/index.svelte";
  import Favorites from "../features/Favorites/index.svelte";
  import { onMount } from "svelte";

  let wifiIsConnected = true;

  onMount(() => {
    if (!wifiIsConnected) {
      navigate("/connect");
    }
  });
</script>

<Router>
  <div
    style="display:flex;flex-grow:1;justify-content:center;align-items:center"
  >
    <Route path="/connect" component={WifiDisconnected} />
    <Route path="/effects" component={EffectsSelection} />
    <Route path="/favorites" component={Favorites} />
    <Route component={ColorSelection} />
  </div>
  <BottomTabNavigator />
</Router>
