<script lang="ts">
  import Ripple from "@smui/ripple";
  import { Icon } from "@smui/common";
  import "./index.css";

  import { useLocation, navigate, link } from "svelte-navigator";

  const location = useLocation();

  const items = [
    { title: "Cores", icon: "palette", link: "/" },
    { title: "Efeitos", icon: "flare", link: "/effects" },
    { title: "Favoritos", icon: "favorite", link: "/favorites" },
  ];
</script>

<div class="bottom-tab-container">
  {#each items as item}
    <div
      class={`bottom-tab-item ${
        $location.pathname === item.link ? "item-active" : ""
      }`}
    >
      <div
        style="padding: 4px 0;"
        on:click={() => navigate(item.link)}
        use:Ripple={{ surface: true, color: "primary" }}
      >
        <Icon class="material-icons">{item.icon}</Icon>
        <p class="title">{item.title}</p>
      </div>
    </div>
  {/each}
</div>
