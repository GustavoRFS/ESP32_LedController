<script lang="ts">
  import CircularProgress from "@smui/circular-progress";

  export let loading = false;
</script>

{#if loading}
  <div
    style="position:absolute;width:100%;height:100%;background:#0009;left:0;top:0;display:flex;justify-content:center;align-items:center;border-radius:4px;"
  >
    <CircularProgress style="height: 28px; width: 28px;" indeterminate />
  </div>
{/if}
